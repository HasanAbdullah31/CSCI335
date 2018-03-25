// Hasan Abdullah: SpellCheck.cpp (10-31-2017)
// Main file for Part 3 of Homework 3. Implements a spell checker using hash
// table with double probing.

#include "DoubleProbing.h"
#include "StringOperations.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;

namespace {

typedef HashTableDouble<string> MyHashTable;   // Can change hash table type.
typedef StringOperations StrOps;

// Read all lines of file @filename and insert them into @hash_table.
// If file @filename is not found, abort.
void FillTable(MyHashTable &hash_table, const string &filename) {
  ifstream ifstr(filename);
  if (ifstr.fail()) {
    cerr << "Unable to open '" << filename << "'!" << endl;
    abort();
  }
  hash_table.MakeEmpty();
  string word;
  while (getline(ifstr, word, '\n'))   // Read the file line-by-line.
    hash_table.Insert(word);
  ifstr.close();
}

// Fill @list with all the misspelled words in file @filename using @dictionary.
// If file @filename is not found, abort.
void GetMisspelledWords(const MyHashTable &dictionary, vector<string> &list,
                        const string &filename) {
  ifstream ifstr(filename);
  if (ifstr.fail()) {
    cerr << "Unable to open '" << filename << "'!" << endl;
    abort();
  }
  // Declare variables here to avoid creating them every time in while loop.
  size_t pos;
  bool check_word, check_second_word;
  string word, second_word, test_word, old_word;
  while (ifstr >> word) {   // Read the file word-by-word.
    StrOps::RemoveSpecialChars(word, 's');   // Erase starting special chars.
    StrOps::RemoveSpecialChars(word, 'e');   // Erase ending special chars.
    pos = word.find("-"); // Words can be separated by -, forming a second word.
    second_word = "";
    // Assume that word and second_word need to be checked for spelling errors.
    check_word = true; check_second_word = true;
    if (pos != string::npos) {   // - was found.
      // Second word starts from char after -, and goes to end of string.
      if (pos+1 < word.length()) {
        second_word = word.substr(pos+1, string::npos);
        // Erase starting special chars of second_word.
        StrOps::RemoveSpecialChars(second_word, 's');
      }
      // First word starts from first char (index 0), and has length pos.
      word = word.substr(0, pos);
      StrOps::RemoveSpecialChars(word, 'e');   // Erase ending special chars.
    }
    // Assert: word and/or second_word can be empty.
    if (word.empty()) check_word = false;   // Don't check an empty word.
    if (second_word.empty()) check_second_word = false;
    
    // Same code for both word and second_word, so avoid repetition with loop.
    for (int i = 0; i < 2; ++i) {
      if (i == 0 && check_word) test_word = word;
      else if (i == 1 && check_second_word) test_word = second_word;
      else continue;   // Go to next iteration of for loop.
      // Assert: 0 < test_word.length()
      if (test_word.length() == 1) {
        if (!StrOps::IsNumber(test_word) && test_word != "a" &&
            test_word != "A" && test_word != "I") list.push_back(test_word);
      }
      // Assert: 1 < test_word.length()
      else if (!StrOps::IsNumber(test_word) &&
               !StrOps::IsOrdinalNumber(test_word)) {
        old_word = test_word;   // Store original case of letters in list.
        StrOps::ToLowerCase(test_word);   // dictionary uses only lower case.
        pos = test_word.length()-1;
        if (test_word[pos-1] == '\'' && test_word[pos] == 's')
          test_word.erase(pos-1, 2);   // Erase the contraction "'s".
        if (!dictionary.Contains(test_word)) list.push_back(old_word);
      }
    } // end for loop
  } // end while (ifstr >> word)
  ifstr.close();
}

// Output all the misspelled words in file @filename using the @dictionary.
// For each misspelled word, output a list of candidate corrections from
// @dictionary as well. If file @filename is not found, abort.
/* Candidate corrections for misspelled words are formed by one of three rules:
   1) Adding one character in each possible position.
   2) Removing one character from the word.
   3) Swapping adjacent characters in the word.
 */
void SpellCheck(const MyHashTable &dictionary, const string &filename) {
  vector<string> misspelled_words;
  set<string> candidate_corrections;
  string original_word;
  GetMisspelledWords(dictionary, misspelled_words, filename);
  size_t num_corrections = 0;
  for (auto current_word : misspelled_words) {
    if (current_word.length() == 1) {
      if (current_word == "i")
        cout << "i should be changed to: I" << endl;
      else
        cout << current_word << " can be changed to: a, A, I" << endl;
    }
    // Assert: 1 < current_word.length()
    else {
      original_word = current_word;
      StrOps::ToLowerCase(current_word);   // dictionary uses only lower case.
      StrOps::AddOneChar(current_word, candidate_corrections);
      StrOps::RemoveOneChar(current_word, candidate_corrections);
      StrOps::SwapAdjChars(current_word, candidate_corrections);
      cout << original_word << " can be changed to: ";
      for (auto correction : candidate_corrections) {
        if (dictionary.Contains(correction)) {
          if (0 < num_corrections) cout << ", ";
          cout << correction;
          ++num_corrections;
        }
      }
      if (num_corrections == 0) cout << "<none found>";
      cout << endl;
      // Reset for next iteration.
      num_corrections = 0;
      candidate_corrections.clear();
    }
  } // end for (auto current_word : misspelled_words)
}

} // namespace

int main(int argc, char** argv) {
  if (argc != 3) {
    cerr << "Usage: " << argv[0] << " <documentfile> <dictionaryfile>" << endl;
    return 1;
  }
  const string document_file(argv[1]);
  const string dictionary_file(argv[2]);
  MyHashTable dictionary;
  FillTable(dictionary, dictionary_file);
  SpellCheck(dictionary, document_file);
  return 0;
}
