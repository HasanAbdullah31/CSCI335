// Hasan Abdullah: chain.h (09-06-2017)
// Chain is a templated container capable of holding an arbitrary number of
// items (of any type). Simply put, it is a scrappy version of a vector.

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <cstddef>
#include <sstream>

namespace teaching_project {
// Chain is a vector-like container with basic functionality: constructors,
// move semantics, destructor, read (from standard input), accessors, and
// overloaded operators. Example use: Chain<int> c1; c1.push_back(1);
// Chain<int> c2{2}; Chaint<int> result = c1 + c2;
// std::cout << result << "; size = " << result.size() << std::endl;
// The output should be: [1 2]; size = 2
template<typename Object>
class Chain {
 public:
  // Default "big five": can add "= default;" instead of implementations

  // Zero-parameter constructor: construct an empty chain
  Chain() {
    size_ = 0;
    array_ = nullptr;
  }

  // Copy-constructor: use new to avoid a shallow copy
  Chain(const Chain &rhs) {
    size_ = rhs.size_;
    if (size_ == 0)
      array_ = nullptr;
    else {
      array_ = new Object[size_];
      for (size_t i = 0; i < size_; ++i)
        array_[i] = rhs.array_[i];
    }
  }

  // Copy-assignment: since the copy-constructor and the move-constructor are
  // already written, the following can be used:
  Chain& operator=(const Chain &rhs) {
    Chain copy = rhs;   // calls the copy-constructor
    std::swap(*this, copy);
    return *this;   // *this is now equivalent to *rhs
  }

  // Move-constructor: rhs data is copied to this, and then rhs is "removed"
  Chain(Chain &&rhs) {
    size_ = rhs.size_;
    array_ = rhs.array_;
    rhs.size_ = 0;
    rhs.array_ = nullptr;   // avoid aliasing by "removing" rhs
  }

  // Move-assignment: just use std::swap() for all variables
  Chain& operator=(Chain &&rhs) {
    std::swap(size_, rhs.size_);
    std::swap(array_, rhs.array_);
    return *this;
  }

  // Destructor: deallocate the block of memory at the pointer to avoid garbage
  ~Chain() {
    if (array_ != nullptr)
      delete[] array_;
  }

  // End of big-five.

  // One parameter constructor: create container of one element, @item
  Chain(const Object& item) {
    size_ = 1;
    array_ = new Object[size_];   // new[] because delete[] in destructor
    array_[0] = item;
  }

  // Read a chain from standard input; assumes correct format (e.g. [2: 31 41])
  void ReadChain() {
    std::cin >> *this;   // let >> operator do the work
  }

  // Accessor function for data member size_
  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the chain.
  // @returns the Object at @location.
  // const version.
  // abort() if out-of-range.
  const Object& operator[](size_t location) const {
    if (size_ == 0) {
      std::cerr << "Unable to access empty Chain with []!" << std::endl;
      abort();
    }
    else if (location < 0 || location >= size_) {
      std::cerr << "Unable to access out-of-range data with []!" << std::endl;
      abort();
    }
    return array_[location];
  }
  // @location: an index to a location in the chain.
  // @returns the Object at @location.
  // non-const version.
  // abort() if out-of-range.
  Object& operator[](size_t location) {   // same code as const version
    if (size_ == 0) {
      std::cerr << "Unable to access empty Chain with []!" << std::endl;
      abort();
    }
    else if (location < 0 || location >= size_) {
      std::cerr << "Unable to access out-of-range data with []!" << std::endl;
      abort();
    }
    return array_[location];
  }

  // Converts a string, @input_string, to template type Object and returns that.
  // Serves as a helper function for >> operator.
  Object StringToObject(const std::string &input_string) const {
    if (!input_string.empty()) {
      Object converted_string;
      std::istringstream stream(input_string);
      if (input_string.find("0x") != std::string::npos)   // 0x was found
	// find function returns std::string::npos if "0x" is not found
	stream >> std::hex >> converted_string;   // hexadecimal (ends with 0x)
      else   // since "0x" was not found, this means input_string is a decimal
	stream >> std::dec >> converted_string;   // decimal (no 0x at end)
      if (stream.fail())
	return Object();
      return converted_string;
    }
    else
      return Object();   // if input_string is empty, return empty Object
  }

  // Adds @item at the end of array_ (after current last element); ++size_
  void push_back(const Object &item) {
    if (size_ == 0) {   // trivial case
      size_ = 1;
      array_ = new Object[size_];
      array_[0] = item;
      return;
    }
    const size_t new_size = size_ + 1;
    Object* new_array = new Object[new_size];
    for (size_t i = 0; i < size_; ++i)
      new_array[i] = array_[i];   // copy all items of array_ into new_array
    new_array[new_size-1] = item;   // insert item at the end of new_array
    delete[] array_;   // free the memory pointed to by array_
    array_ = new_array;   // array_ now takes on the memory of new_array
    new_array = nullptr;
    ++size_;   // data member size_ incremented after push_back() called
  }

  // @c1: A chain.
  // @c2: A second chain.
  // @return the concatenation of the two chains.
  friend Chain operator+(const Chain &c1, const Chain &c2) {
    Chain result{c1};   // copy contents of c1 into result
    // use push_back() function to insert all items of c2 into result
    for (size_t i = 0; i < c2.size_; ++i)
      result.push_back(c2[i]);   // side eff: ++result.size_ each time
    // assert: result.size_ = c1.size_ + c2.size_
    return result;
  }
  // Same as above + operator, except concatenates a Chain and a Object
  // e.g. Chain<string> c{"hi"}; cout << c + "world"; // output: "[hi world]"
  friend Chain operator+(const Chain &c1, const Object &c2) {
    Chain result{c1};   // copy contents of c1 into result
    result.push_back(c2);
    return result;
  }

  // Overloading the >> operator (good practice to overload BOTH >> and <<)
  friend std::istream &operator>>(std::istream &in, Chain &a_chain) {
    std::string input;
    getline(in, input, '\n');
    // Error checking of the input:
    if (input.size() < 4) abort();   // smallest input: "[0:]"
    else if (input[0] != '[' || input[input.size()-1] != ']') abort();
    // find function returns std::string::npos if ":" is not found
    else if (input.find(":") == std::string::npos) abort();
    else if (input.find("  ") != std::string::npos) abort();
    // valid input: "[<desired_size>: <i_1> <i_2> <...> <i_desired_size>]"
    std::string desired_size = "";
    const size_t index_of_colon = input.find_first_of(':');
    for (size_t a = 1; a < index_of_colon; ++a)   // a = 1: start after the '['
      desired_size += input[a];
    try {
      int size = std::stoi(desired_size);   // throws invalid_argument on fail
      int num_spaces = 0;
      for (size_t b = 1; b < input.size()-1; ++b)   // skip the '[' and ']'
	if (input[b] == ' ') ++num_spaces;
      if (size != num_spaces) abort();   // spaces determine number of items
    } catch (const std::invalid_argument &ia) { abort(); }
    // Error checking done; now insert the items of input into array_
    std::string temp = "";   // temp will hold each item to be put in array_
    size_t start = input.find_first_of(':');
    start += 2;   // e.g. [3: 1 2 3]; start indexed the ':', now indexes the '1'
    for (size_t i = start; i < input.size()-1; ++i) {
      // goes from start item to last item; ends right before ']' (at size-2)
      temp += input[i];
      if (input[i+1] == ' ' || input[i+1] == ']') {   // delimiters for items
	Object item = a_chain.StringToObject(temp);
	a_chain.push_back(item);   // side eff: ++a_chain.size_ for added item
	temp = "";   // reset temp for holding next item
	++i;   // go to the ' ', so the ++i in the loop will start on next item
      }
    }
    return in;
  }

  // Overloading the << operator
  // Assumes Object has overloaded << (e.g. int, char, string)
  friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain) {
    const size_t size = a_chain.size_;   // store in variable to avoid typing
    if (size == 0) {
      out << "[]" << std::endl;
      return out;
    }
    out << "[";
    // loop ends at size-2 to avoid printing last element with a space after it
    for (size_t i = 0; i < size-1; ++i)
      out << a_chain.array_[i] << " ";
    // now print the last element, followed by a ] and a newline
    out << a_chain.array_[size-1] << "]" << std::endl;
    return out;
  }

 private:
  size_t size_;
  Object* array_;
};

}   // namespace teaching_project

#endif // CSCI_335_HOMEWORK1_CHAIN_
