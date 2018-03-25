// Hasan Abdullah: test_tree.cc (09-30-2017)
// Main file for Part2(b) of Homework 2. Constructs search tree from database,
// prints # of nodes, computes avg. depth, searches for strings in a file,
// removes every other sequence in tree, and counts total # of recursive calls.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
using namespace Part_1;

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be empty.
// Parses @db_filename to construct search tree @a_tree and prints various
// calculations using TreeType methods and @seq_filename.
// Assumes the files are of the correct formats; aborts if file(s) not found.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // 1: Parse the database and construct a search tree (same as in Part2(a))
  ifstream ifstr(db_filename);
  if (ifstr.fail()) {
    cerr << "Unable to open '" << db_filename << "'!" << endl;
    abort();
  }
  // the first 10 lines of the file is the header; ignore them
  for (int i = 0; i < 10; ++i)
    ifstr.ignore(999, '\n');
  /* after the header, each line of the file is in the following format:
     enzyme_acronym/recognition_sequence/.../recognition_sequence//      */
  
  // create objects here to avoid creating in while loop
  string db_line, an_enz_acro, a_rec_seq;
  size_t delim_pos, start_pos;
  SequenceMap new_sequence_map;
  while (getline(ifstr, db_line, '\n')) {   // read the file line-by-line
    // the first part of the line is enzyme_acronym/
    delim_pos = db_line.find_first_of('/');
    an_enz_acro = db_line.substr(0, delim_pos);
    // the next parts of the line are recognition_sequence/<...>// where
    // <...> can be other recognition sequences separated by /
    // assumes that there is at least 1 recognition sequence
    while (delim_pos != string::npos && db_line[delim_pos+1] != '/') {
      // if db_line[delim_pos]+db_line[delim_pos+1]=="//", end of line reached
      start_pos = delim_pos+1;   // rec. seq. starts right after the '/'
      delim_pos = db_line.find('/', start_pos);   // find the next '/'
      a_rec_seq = db_line.substr(start_pos, delim_pos - start_pos);
      new_sequence_map = SequenceMap(a_rec_seq, an_enz_acro);
      // this insert function uses the Merge function of SequenceMap
      a_tree.insert(new_sequence_map);
    }
  }
  ifstr.close();
  
  // 2: Print number of nodes, N, in the tree:
  int N = a_tree.size();
  cout << "2: " << N << endl;
  
  // 3a: Compute and print average depth of search tree (internal_path_length/N)
  int internal_path_length = a_tree.totalHeight();
  float average_depth = (float)internal_path_length / (float)N;
  cout << "3a: " << average_depth << endl;
  // 3b: Compute and print ratio of the average depth to log_2 N
  cout << "3b: " << average_depth / log2(N) << endl;
  
  // Search tree for strings in seq_filename
  ifstr.open(seq_filename);
  if (ifstr.fail()) {
    cerr << "Unable to open '" << seq_filename << "'!" << endl;
    abort();
  }
  int num_queries = 0, successful_queries = 0,
      recursive_calls = 0, total_recursive_calls = 0;
  bool found;
  string seq;
  while (ifstr >> seq) {
    ++num_queries;
    recursive_calls = 0;
    found = a_tree.find(seq, recursive_calls);   // recursive_calls updated
    if (found)
      ++successful_queries;
    total_recursive_calls += recursive_calls;
  }
  ifstr.close();
  // 4a: Print total number of successful queries
  cout << "4a: " << successful_queries << endl;
  // 4b: Print average number of recursive calls
  float avg_recursive_calls = (float)total_recursive_calls / (float)num_queries;
  cout << "4b: " << avg_recursive_calls << endl;
  
  // Remove every other sequence in seq_filename from tree
  ifstr.open(seq_filename);
  int attempted_removes = 0, successful_removes = 0;
  total_recursive_calls = 0;
  while (ifstr >> seq) {   // similar code as above
    ++attempted_removes;
    recursive_calls = 0;
    found = a_tree.remove(seq, recursive_calls);   // recursive_calls updated
    if (found)
      ++successful_removes;
    total_recursive_calls += recursive_calls;
    ifstr.seekg(1, ios_base::cur);   // go to next line
    ifstr.ignore(999, '\n');   // ignore this line
  }
  ifstr.close();
  // 5a: Print total number of successful removes
  cout << "5a: " << successful_removes << endl;
  // 5b: Print average number of recursive calls
  avg_recursive_calls = (float)total_recursive_calls / (float)attempted_removes;
  cout << "5b: " << avg_recursive_calls << endl;
  
  // Redo steps 2 and 3:
  // 6a: Print number of nodes, N, in the tree:
  N = a_tree.size();
  cout << "6a: " << N << endl;
  // 6b: Compute and print average depth of search tree (internal_path_length/N)
  internal_path_length = a_tree.totalHeight();
  average_depth = (float)internal_path_length / (float)N;
  cout << "6b: " << average_depth << endl;
  // 6c: Compute and print ratio of the average depth to log_2 N
  cout << "6c: " << average_depth / log2(N) << endl;
  
  return;
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
