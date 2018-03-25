// Hasan Abdullah: TestRandomGraph.cpp (11-22-2017)
// Main file for Part 3 of Homework 4. Generates a random undirected graph of
// N vertices using a union-find data structure (disjoint set), and then prints
// number of edges, smallest, largest, and average out-degrees for a vertex.

#include "DisjSets.h"

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
using namespace std;

namespace {

// Vector of vector of ints (representing the vertex number).
// i.e. adjlist[k] is a vector of vertices that are adjacent to vertex k.
typedef vector< vector<int> > AdjList;

// Return true if @vec contains @x, else return false.
bool contains(const vector<int> &vec, const int &x) {
  for (auto val : vec) if (val == x) return true;
  return false;
}

// Return a random int value in range(0, @max_size-1).
int rand(const int &max_size) { return std::rand() % max_size; }

} // namespace

int main(int argc, char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <maximum_number_of_nodes>" << endl;
    return 1;
  }
  const int N{stoi(argv[1])};
  if (N < 0) {
    cerr << "Maximum number of nodes cannot be less than 0!" << endl;
    return 1;
  }
  int num_edges = 0;
  int smallest_out_degree = 0;
  int largest_out_degree = 0;
  double avg_out_degree = 0.0;
  if (1 < N) {
    // Seed RNG for different outputs on each run of program.
    srand(time(0));
    int v1, v2;
    DisjSets sets(N);
    AdjList vertices(N);
    while (!sets.isConnected()) {
      // v1 cannot equal v2, in order to disallow loops.
      v1 = rand(N); do { v2 = rand(N); } while (v2 == v1);
      if ( vertices[v1].empty() or vertices[v2].empty() or
           not contains(vertices[v1], v2) ) {
        // Last condition occurs when both v1 and v2 are connected to any
        // other vertices. This allows cycles in the graph.
        vertices[v1].push_back(v2);   // v1 -> v2
        vertices[v2].push_back(v1);   // v1 <-> v2 (b/c of undirected graph)
        sets.unionSets(sets.find(v1), sets.find(v2));
        ++num_edges; // unionSets(root(v1), root(v2)) == add edge b/w v1 and v2.
      }
    }
    int num_out_degrees;
    vector<int> out_degree_sizes(N);
    for (int i = 0; i < N; ++i) {
      num_out_degrees = vertices[i].size();
      avg_out_degree += num_out_degrees;   // Total sum, divide by N later.
      out_degree_sizes[i] = num_out_degrees;
    }
    avg_out_degree /= (double)N;
    std::sort(out_degree_sizes.begin(), out_degree_sizes.end());
    smallest_out_degree = out_degree_sizes[0];
    largest_out_degree = out_degree_sizes[N-1];
  } // end if (1 < N)
  // If N (maximum number of nodes) is 0 or 1, all the following values are 0.
  cout << "Number of edges: " << num_edges << endl;
  cout << "Smallest out-degree for a vertex: " << smallest_out_degree << endl;
  cout << "Largest out-degree for a vertex: " << largest_out_degree << endl;
  cout << "Average out-degree for a vertex: " << avg_out_degree << endl;
  return 0;
}
