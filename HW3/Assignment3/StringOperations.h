// Hasan Abdullah: StringOperations.h (10-31-2017)
// Static class of utility functions for chars and strings.

#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

#include <string>
#include <set>
using std::string;

// StringOperations class
//
// CONSTRUCTION: None (static class)
// Call a function f() of StringOperations like so: StringOperations::f();
//
// ******************************PUBLIC OPERATIONS******************************
// *********c is char, x is string, L is set<string>; & is pass-by-ref.*********
// bool IsSpecialChar(c)       --> Return true if c is a special char, else
//                             return false.
// bool IsNumber(x)            --> Return true if x is a string of a number(s),
//                             else return false. If x is empty, return false.
// bool IsOrdinalNumber(x)     --> Return true if x is an ordinal number, else
//                             return false. If length(x)<3, return false.
// void ToLowerCase(&x)        --> Set all alphabet chars in x to lower-case.
// void RemoveSpecialChars(&x) --> Remove all non-alphanumeric chars from x.
// [ overloaded with (&x, c)]  --> c == 's': only remove special chars from
//                             start of x. c == 'e', only remove special chars
//                             from end of x. Else, remove all special chars.
// void AddOneChar(x, &L)      --> Insert into L strings formed by adding one
//                             char in each pos of x. If x is empty, return.
// void RemoveOneChar(x ,&L)   --> Insert into L strings formed by removing one
//                             char from x. If length(x)<2, return.
// void SwapAdjChars(x, &L)    --> Insert into L strings formed by swapping
//                             adjacent chars in x. If x is empty, return. If x
//                             is length 1, only insert x into L.
// *****************************************************************************

class StringOperations {
 private:
  StringOperations();   // Unable to create an instance of this class.
 public:
  // Return true if @c is a special char, else return false.
  static bool IsSpecialChar(const char &c) {
    const string SPECIAL_CHARS = "!@#$%^&*()-_=+[{]}\\|;:'\",<.>/?";
    bool is_special_char = false;
    for (auto a_special_char : SPECIAL_CHARS) {
      if (c == a_special_char) {
        is_special_char = true;
        break;
      }
    }
    return is_special_char;
  }
  
  // Return true if @word is a string of a number(s), else return false.
  // If @word is empty, return false.
  static bool IsNumber(const string &word) {
    if (word.empty()) return false;
    if (word.length() == 1) return isdigit((int)word[0]);
    bool is_number = true;
    for (auto symbol : word) {
      if ( !isdigit((int)symbol) && symbol != '-' && symbol != '.' ) {
        is_number = false;
        break;
      }
    }
    return is_number;
  }
  
  // Return true if @word is an ordinal number, else return false.
  // If length of @word is less than 3, return false.
  static bool IsOrdinalNumber(const string &word) {
    if (word.length() < 3) return false;
    size_t second_to_last_pos = word.length()-2;
    string last_two_chars = word.substr(second_to_last_pos, 2);
    string other_chars = word.substr(0, second_to_last_pos);
    // other_chars are the chars before the "st", "nd", "rd", or "th".
    if (IsNumber(other_chars)) {
      if (word == "11th" || word == "12th" || word == "13th") return true;
      char last_char_of_other_chars = other_chars[other_chars.length()-1];
      // Assert: word is not "11th", "12th", or "13th".
      if (last_char_of_other_chars == '1') {
        if (last_two_chars == "st") return true;
      }
      else if (last_char_of_other_chars == '2') {
        if (last_two_chars == "nd") return true;
      }
      else if (last_char_of_other_chars == '3') {
        if (last_two_chars == "rd") return true;
      }
      // Assert: last_char_of_other_chars is not '1', '2', or '3'.
      else if (last_two_chars == "th") {
        return true;
      }
    }
    return false;
  }
  
  // Set all chars of @word to lower-case (if valid). If @word is empty, return.
  static void ToLowerCase(string &word) {
    if (word.empty()) return;
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
  }
  
  // Remove special chars from @word. By default, all special chars are removed.
  // If @c is set to 's', only erase starting special chars, and if @c is set to
  // 'e', only erase ending special chars. If @word is empty, return.
  static void RemoveSpecialChars(string &word, const char &choice = 'a') {
    if (word.empty()) return;
    switch (choice) {
    case 's':
      for (size_t i = 0; i < word.length(); ++i) {
        if (IsSpecialChar(word[i])) word.erase(i, 1);
        else return;
      }
      break;
    case 'e':
      for (int j = word.length()-1; 0 <= j; --j) {
        if (IsSpecialChar(word[j])) word.erase(j, 1);
        else return;
      }
      break;
    default:
      string new_word = "";
      for (auto current_char : word)
        if (!IsSpecialChar(current_char)) new_word += current_char;
      word = new_word;
    } // end switch
  }
  
  // Insert into @list strings formed by adding one char in each pos of @word.
  // If @word is empty, return.
  static void AddOneChar(const string &word, std::set<string> &list) {
    if (word.empty()) return;
    const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";
    string new_word = word;
    // pos at word.length() is pos after last char of word, can insert there.
    for (size_t pos = 0; pos <= word.length(); ++pos) {
      for (auto letter : ALPHABET) {
        new_word.insert(pos, 1, letter);   // Insert 1 occurence of it.
        list.insert(new_word);
        new_word = word;   // Reset back to original word for next iteration.
      }
    }
  }
  
  // Insert into @list strings formed by removing one char from @word.
  // If length of @word is less than 2, return.
  static void RemoveOneChar(const string &word, std::set<string> &list) {
    if (word.length() < 2) return;
    string new_word = word;
    for (size_t pos = 0; pos < word.length(); ++pos) {
      new_word.erase(pos, 1);
      list.insert(new_word);
      new_word = word;   // Reset back to original word for next iteration.
    }
  }
  
  // Insert into @list strings formed by swapping adjacent chars in @word.
  // If @word is empty, return. If it is length 1, only insert @word into @list.
  static void SwapAdjChars(const string &word, std::set<string> &list) {
    if (word.empty()) return;
    if (word.length() == 1) {
      list.insert(word);
      return;
    }
    string new_word = word;
    for (size_t pos = 0; pos < word.length()-1; ++pos) {
      std::swap(new_word[pos], new_word[pos+1]);
      list.insert(new_word);
      new_word = word;   // Reset back to original word for next iteration.
    }
  }
};

#endif // STRING_OPERATIONS_H
