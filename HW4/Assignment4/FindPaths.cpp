// Hasan Abdullah: FindPaths.cpp (11-22-2017)
// Main file for Part 2 of Homework 4. Uses Dijkstra's Algorithm to find the
// shortest paths from a given starting vertex to all vertices in the graph
// file, and then prints the paths and costs to every destination.

#include "BinaryHeap.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cfloat>
#include <vector>
using namespace std;

namespace {

// pair.first is weight of edge and pair.second is vertex number.
typedef pair<float,int> Vertex;
// i.e. dgraph[k] is a vector of vertices that are adjacent to vertex k.
typedef vector< vector< Vertex > > DGraph;

// Parse @filename to create and return a directed graph (DGraph).
// Assumes that file @filename is of the correct format (also assumes that the
// list of connected vertices on each line does not contain two same vertices).
// If file @filename is not found, output error message and abort.
DGraph GetDirectedGraph(const string &filename) {
  ifstream file{filename};
  if (file.fail()) {
    cerr << "Unable to open '" << filename << "'!" << endl;
    abort();
  }
  // First line of file is number of vertices.
  int num_vertices;
  file >> num_vertices;
  file.ignore(99, '\n');
  DGraph graph(num_vertices);
  // The following lines are of the form:
  // <vertex> <connected vertex1> <weight1> <connected vertex2> <weight2> ...
  string line; int vertex, connected_vertex; float weight;
  while (getline(file, line)) {
    if (line.empty()) continue;
    stringstream line_stream{line};
    line_stream >> vertex;
    while (line_stream >> connected_vertex >> weight)
      // -1 because the vertices in the file are 1...N (not 0...N-1).
      graph[vertex-1].push_back({weight,connected_vertex-1});
  }
  file.close();
  return graph;
}

// Print shortest paths from the @start_vertex to all the vertices in @graph.
// Assumes @start_vertex is in 1...N (not 0...N-1).
// If @start_vertex is out of bounds in @graph, output error message and abort.
void PrintShortestPaths(const DGraph &graph, int start_vertex) {
  const int N = graph.size();
  --start_vertex;   // Convert from 1...N to 0...N-1.
  if (start_vertex < 0 or N <= start_vertex) {
    cerr << "Start vertex " << start_vertex+1 << " is out of bounds!" << endl;
    abort();
  }
  // Create a priority queue (binary heap) of vertices to be preprocessed.
  // By default, pair.first is used for comparison; Vertex.first is weight.
  BinaryHeap<Vertex> pq_vertices;
  // Also create a vector of distances, initializing to FLT_MAX (i.e. INFINITY).
  vector<float> distances(N, FLT_MAX);
  // Start with the start_vertex, which has distance 0 to itself.
  pq_vertices.insert({0.0f,start_vertex});
  distances[start_vertex] = 0.0f;
  float cur_weight, new_weight;
  int cur_vertex, min_vertex;
  vector<int> prev_vertex(N);
  // prev_vertex[k] is vertex that comes before vertex k in the optimal path.
  while (!pq_vertices.isEmpty()) {
    // Store the vertex number of minimum weight after removing it from queue.
    min_vertex = pq_vertices.deleteMin().second;
    for (const Vertex connected_vertex : graph[min_vertex]) {
      cur_weight = connected_vertex.first;
      cur_vertex = connected_vertex.second;
      new_weight = distances[min_vertex] + cur_weight;
      // If there is a shorter path to cur_vertex through min_vertex,
      // update the distance of cur_vertex and push onto the queue.
      if (new_weight < distances[cur_vertex]) {   // "Relaxation" step
        distances[cur_vertex] = new_weight;
        pq_vertices.insert({distances[cur_vertex],cur_vertex});
        prev_vertex[cur_vertex] = min_vertex;
      }
    }
  } // end while (!pq_vertices.isEmpty())
  int original_target;
  vector<int> path;
  for (int target = 0; target < N; ++target) {
    // During output, print the 1...N forms instead of 0...N-1 (so do +1).
    cout << target+1 << ": ";
    if (distances[target] == FLT_MAX) {
      cout << "No path." << endl;
      continue;
    }
    if (target == start_vertex) {
      cout << start_vertex+1 << ", Cost: 0.0." << endl;
      continue;
    }
    original_target = target;
    // Build path backwards, following prev_vertex[target].
    path = {target};
    while (prev_vertex[target] != start_vertex) {
      target = prev_vertex[target];
      path.insert(path.begin(), target);   // i.e. push_front(target)
    }
    target = original_target;
    cout << start_vertex+1 << ", ";
    for (const int vertex : path) cout << vertex+1 << ", ";
    cout << "Cost: " << setprecision(1) << fixed
         << distances[target] << "." << endl;
  }
}

} // namespace

int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <graphfilename> <startvertex>" << endl;
    return 1;
  }
  const string graph_filename{argv[1]};
  const int start_vertex{stoi(argv[2])};
  DGraph graph = GetDirectedGraph(graph_filename);
  PrintShortestPaths(graph, start_vertex);
  return 0;
}
