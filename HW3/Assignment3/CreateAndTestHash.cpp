// Hasan Abdullah: CreateAndTestHash.cpp (10-30-2017)
// Main file for Part 1 and Part 2 of Homework 3. Tests 3 different hash tables
// (linear, quadratic, and double probing) with 2 text files (list of words and
// words to query).

#include "LinearProbing.h"
#include "QuadraticProbing.h"
#include "DoubleProbing.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

namespace {

// Helper method for TestFunctionForHashTable(). Print formatted output.
template <typename Type>
void Print(const string &msg, const Type &x) {
  cout << setw(28) << setfill(' ') << msg << x << endl;
}

// Read all words from file @words_filename and insert them into @hash_table.
// Print to standard output: total number of elements in table, size of table,
// load factor, total number of collisions, and average number of collisions.
// Also check whether each word in file @query_filename is in table or not;
// if found, print the word, the string "Found" and number of probes used, and
// if not found, do the same except replace "Found" with "Not Found".
// If files @words_filename or @query_filename are not found, abort.
template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) {
  cout << "TestFunctionForHashTable..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl << endl;
  ifstream ifstr(words_filename);
  if (ifstr.fail()) {
    cerr << "Unable to open '" << words_filename << "'!" << endl;
    abort();
  }
  hash_table.MakeEmpty();
  string word;
  while (getline(ifstr, word, '\n'))   // Read the file line-by-line.
    hash_table.Insert(word);
  ifstr.close();
  
  size_t num_items = hash_table.Num_Elements();
  Print("Number of items: ", num_items);
  size_t size = hash_table.Size();
  Print("Size of hash table: ", size);
  float load_factor = (float)num_items/(float)size;
  Print("Load factor: ", load_factor);
  int num_collisions = hash_table.Num_Collisions();
  Print("Collisions: ", num_collisions);
  float avg_collisions = (float)num_collisions/(float)num_items;
  Print("Avg. number of collisions: ", avg_collisions);
  cout << endl;
  
  ifstr.open(query_filename);
  if (ifstr.fail()) {
    cerr << "Unable to open '" << query_filename << "'!" << endl;
    abort();
  }
  while (getline(ifstr, word, '\n')) {
    cout << setw(12) << setfill(' ') << word;
    hash_table.Reset_Collisions();   // Set number of probes used to 0 at start.
    cout << setw(12) << setfill(' ');
    if (hash_table.Contains(word)) cout << " Found;";
    else cout << " Not Found;";
    cout << " Number of probes used: " << hash_table.Num_Collisions() << endl;
  }
  ifstr.close();
}

} // namespace

int main(int argc, char** argv) {
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 1;
  }
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);
  
  if (param_flag == "linear") {
    HashTableLinear<string> linear_probing_table;
    TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);
  } else if (param_flag == "quadratic") {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);
  } else if (param_flag == "double") {
    HashTableDouble<string> double_probing_table;
    TestFunctionForHashTable(double_probing_table, words_filename, query_filename);
  } else {
    cerr << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}
