// Hasan Abdullah: query_tree.cc (09-30-2017)
// Main file for Part2(a) of Homework 2. Reads in a database of enzyme acronyms
// and recognition sequences into a tree (either BST or AVL) as SequenceMaps.
// User queries the tree with 3 rec. seq.'s; if found, prints the enz. acro.'s.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"
using namespace Part_1;

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be empty.
// Parses @db_filename to construct search tree @a_tree. The user separately
// inputs 3 recognition sequences to query; if the sequence exists, all the
// corresponding enzymes for that recognition sequence will be printed.
// Assumes the file is of the correct format; aborts if file not found.
template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
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
  
  string user_input_rec_seq;
  SequenceMap query_item;
  for (int i = 0; i < 3; ++i) {
    cin >> user_input_rec_seq;
    // the contains function of both trees takes in as arg a Comparable, in this
    // case SequenceMap, so convert user_input_rec_seq to SequenceMap
    query_item = SequenceMap(user_input_rec_seq, "foo");
    if (!a_tree.contains(query_item, true))   // prints enzyme acronyms if false
      cout << "Not Found" << endl;
  }
}

}  // namespace

int
main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
