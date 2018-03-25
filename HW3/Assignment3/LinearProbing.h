// Hasan Abdullah: LinearProbing.h (10-30-2017)
// A hash table using linear probing and standard operations.

#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include "QuadraticProbing.h"

// HashTableLinear class (subclass of HashTable)
//
// CONSTRUCTION: zero parameter, one paramater (size_t)
//
// ******************PUBLIC OPERATIONS (inherited from HashTable)**************
// void MakeEmpty( )        --> Empty table
// void Reset_Collisions( ) --> Set total number of collisions to 0
// bool Contains( x )       --> Return true if x is present, false otherwise
// bool Insert( x )         --> Insert x and return true if successful, false
//                          otherwise; if table is more than half full, double
//                          the size of the table and rehash the elements
// bool Remove( x )         --> Remove x and return true if successful (x is in
//                          the table), false otherwise (x is not in the table)
// size_t Size( )           --> Return size of table
// size_t Num_Elements( )   --> Return number of elements in table
// int Num_Collisions( )    --> Return total number of collisions that occurred
// ****************************************************************************

// Linear probing implementation. A HashTableLinear IS-A HashTable.
template <typename HashedObj>
class HashTableLinear : public HashTable<HashedObj> {
 public:
  // One parameter constructor that can be zero paramater as well (size=101).
  // Initialize size of table to prime number at least as large as @size.
  explicit HashTableLinear(size_t size = 101) : HashTable<HashedObj>{size}
    { ; }
 private:
  // Overload the FindPos() function of superclass HashTable.
  // Return position that @x should be in by using hashing and probing.
  size_t FindPos(const HashedObj & x) const {
    // Accessing protected data of templated superclass requires their fully
    // qualified names, so use this-><data_member> as a workaround.
    size_t offset = 1;   // Linear probing increments pos by 1 each time.
    size_t current_pos = this->InternalHash(x);
    while ((this->array_)[current_pos].info_ != this->EMPTY &&
           (this->array_)[current_pos].element_ != x) {
      ++(this->num_collisions_);
      current_pos += offset;   // Compute ith probe.
      if (current_pos >= (this->array_).size())
        current_pos -= (this->array_).size();   // Wrap around.
    }
    return current_pos;
  }
};

#endif // LINEAR_PROBING_H
