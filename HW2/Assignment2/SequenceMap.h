// Hasan Abdullah: SequenceMap.h (09-29-2017)
// SequenceMap is a simple class that holds a recognition sequence string and
// a vector of enzyme acronym strings. This is Part1 of Homework 2.

#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H

#include <string>
#include <vector>

namespace Part_1 {

// SequenceMap class
//
// CONSTRUCTION: SequenceMap( )                    --> Empty constructor
//               SequenceMap( rec_seq, enz_acro )  --> Two string constructor
//
// ******************PUBLIC OPERATIONS (sm is a SequenceMap object)************
// bool operator<( sm )            --> Returns true if this object < sm object
// ostream& operator<<( out, sm )  --> Output sm via ostream object out
// Merge( sm )                     --> Adds sm to this object; sm not affected
// ****************************************************************************
class SequenceMap {
 public:
  // The Big Five (use defaults since no private data members are pointers)
  SequenceMap(const SequenceMap &sm) = default;
  SequenceMap(SequenceMap &&sm) = default;
  SequenceMap& operator=(const SequenceMap &sm) = default;
  SequenceMap& operator=(SequenceMap &&sm) = default;
  ~SequenceMap() = default;
  
  // Empty constructor: recognition_sequence_ and enzyme_acronyms_ are empty
  SequenceMap() {
    recognition_sequence_ = "";
  }
  
  // Constructor that assigns @a_rec_seq to recognition_sequence_ and pushes
  // @an_enz_acro onto the empty vector enzyme_acronyms_ (making its size 1)
  SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro) {
    recognition_sequence_ = a_rec_seq;
    enzyme_acronyms_.push_back(an_enz_acro);
  }
  
  // < operates on regular string comparison b/w recognition_sequence_ strings
  bool operator<(const SequenceMap &rhs) const {
    return this->recognition_sequence_ < rhs.recognition_sequence_;
  }
  
  // Overloaded << operator
  friend std::ostream& operator<<(std::ostream &out, const SequenceMap &sm) {
    for (std::string x: sm.enzyme_acronyms_)
      out << x << " ";
    return out;
  }
  
  // Assumes recognition_sequence_ == @other_sequence.recognition_sequence_
  // (aborts if they're not equal). Merges @other_sequence.enzyme_acronyms_ with
  // enzyme_acronyms_; @other_sequence will not be affected.
  void Merge(const SequenceMap &other_sequence) {
    if (recognition_sequence_ != other_sequence.recognition_sequence_) {
      std::cerr << "In function Merge(const SequenceMap&)..."
		<< "recognition sequences don't match!" << std::endl;
      abort();
    }
    if (other_sequence.enzyme_acronyms_.size() == 0)
      return;   // no need to do anything if empty vector is to be added
    for (std::string x: other_sequence.enzyme_acronyms_)
      enzyme_acronyms_.push_back(x);
  }
  
 private:
  std::string recognition_sequence_;
  std::vector<std::string> enzyme_acronyms_;
};

}   // namespace Part_1

#endif // SEQUENCE_MAP_H
