// Hasan Abdullah: CreateGraphAndTest.cpp (11-22-2017)
// Main file for Part 1 of Homework 4. Reads in a directed graph from a text
// file into an adjacency list, and then tests and prints whether various pairs
// of vertices in a query file are adjacent in the adjacency list or not.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cfloat>
#include <vector>
#include <list>
using namespace std;

namespace {

// Vector of lists of pairs; pair.first is vertex number, pair.second is weight
// of edge. i.e. adjlist[k] is a list of vertices that are adjacent to vertex k.
typedef vector< list< pair<int,float> > > AdjList;

// Parse @filename to create and return an AdjList.
// Assumes that file @filename is of the correct format (also assumes that the
// list of connected vertices on each line does not contain two same vertices).
// If file @filename is not found, output error message and abort.
AdjList GetAdjacencyList(const string &filename) {
  ifstream file{filename};
  if (file.fail()) {
    cerr << "Unable to open '" << filename << "'!" << endl;
    abort();
  }
  // First line of file is number of vertices.
  int num_vertices;
  file >> num_vertices;
  file.ignore(99, '\n');
  AdjList adj_list(num_vertices);
  // The following lines are of the form:
  // <vertex> <connected vertex1> <weight1> <connected vertex2> <weight2> ...
  string line; int vertex, connected_vertex; float weight;
  while (getline(file, line)) {
    if (line.empty()) continue;
    stringstream line_stream{line};
    line_stream >> vertex;
    while (line_stream >> connected_vertex >> weight)
      // -1 because the vertices in the file are 1...N (not 0...N-1).
      adj_list[vertex-1].push_back({connected_vertex-1,weight});
  }
  file.close();
  return adj_list;
}

// Return the pair.second of the pair.first in @list which == @x, and if there
// is no pair.first in @list which == @x, return FLT_MAX.
float contains(const list< pair<int,float> > &list, const int &x) {
  for (auto pair : list) if (pair.first == x) return pair.second;
  return FLT_MAX;
}

// Test each pair of vertices in @filename for adjacency in @adj_list. If they
// are adjacent, print the weight of the edge that connects them, else print
// "Not connected". Assumes that file @filename is of the correct format.
// If file @filename is not found, output error message and abort.
void PrintAdjacentVertices(const AdjList &adj_list, const string &filename) {
  ifstream file{filename};
  if (file.fail()) {
    cerr << "Unable to open '" << filename << "'!" << endl;
    abort();
  }
  int vertex1, vertex2; float weight;
  const int N = adj_list.size();
  while (file >> vertex1 >> vertex2) {
    cout << vertex1 << " " << vertex2 << ": ";
    // Vertices in the file are 1...N, instead of the C++ indexing 0...N-1.
    --vertex1; --vertex2;
    // If either vertex is out of bounds, they don't exist (no connections).
    if (vertex1 < 0 or N <= vertex1 or vertex2 < 0 or N <= vertex2) {
      cout << "Not connected" << endl;
      continue;
    }
    weight = contains(adj_list[vertex1], vertex2);
    if (weight != FLT_MAX)
      cout << "Connected, weight of edge is " << setprecision(1) << fixed
           << weight << endl;
    else
      cout << "Not connected" << endl;
  }
  file.close();
}

} // namespace

int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <graphfilename> <queryfilename>" << endl;
    return 1;
  }
  const string graph_filename{argv[1]};
  const string query_filename{argv[2]};
  AdjList adj_list = GetAdjacencyList(graph_filename);
  PrintAdjacentVertices(adj_list, query_filename);
  return 0;
}
