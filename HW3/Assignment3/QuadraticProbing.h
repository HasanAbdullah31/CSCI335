// Hasan Abdullah: QuadraticProbing.h (10-30-2017)
// A hash table using quadratic probing and standard operations.

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>

// HashTable class
//
// CONSTRUCTION: zero parameter, one paramater (size_t)
//
// ******************PUBLIC OPERATIONS*****************************************
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

namespace {

// Internal function to test if a positive number is prime.
bool IsPrime(size_t n) {
  if (n == 2 || n == 3)
    return true;
  if (n == 1 || n % 2 == 0)
    return false;
  for (unsigned int i = 3; i * i <= n; i += 2)
    if (n % i == 0)
      return false;
  return true;
}

// Internal function to return a prime number at least as large as n.
int NextPrime(size_t n) {
  if (n % 2 == 0)
    ++n;
  while (!IsPrime(n))
    n += 2;
  return n;
}

} // namespace

// Quadratic probing implementation.
template <typename HashedObj>
class HashTable {
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};
  
  // One parameter constructor that can be zero paramater as well (size=101).
  // Initialize size of table to prime number at least as large as @size.
  explicit HashTable(size_t size = 101) : array_(NextPrime(size))
    { num_collisions_ = 0; MakeEmpty(); }
  
  // Virtual destructor defined because function FindPos() is virtual.
  virtual ~HashTable() {}
  
  // Return true if @x is active in table, false otherwise.
  bool Contains(const HashedObj & x) const
  { return IsActive(this->FindPos(x)); }
  
  // Set current_size_ to 0 and set all elements to empty.
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }
  
  // If FindPos(x) is not active, insert @x as active in table and return true.
  // If an element already exists at FindPos(x), return false. If table is more
  // than half full after insertion, double size of table and rehash elements.
  bool Insert(const HashedObj & x) {
    // Insert x as active.
    size_t current_pos = this->FindPos(x);
    if (IsActive(current_pos))
      return false;
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    // Rehash; see Section 5.5.
    if (++current_size_ > array_.size() / 2)
      Rehash();
    return true;
  }
  
  // Same as above, but using move semantics.
  bool Insert(HashedObj && x) {
    // Insert x as active.
    size_t current_pos = this->FindPos(x);
    if (IsActive(current_pos))
      return false;
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;
    // Rehash; see Section 5.5.
    if (++current_size_ > array_.size() / 2)
      Rehash();
    return true;
  }
  
  // If FindPos(x) is active, set @x to deleted in table and return true.
  // If an element does not exist at FindPos(x), return false.
  bool Remove(const HashedObj & x) {
    size_t current_pos = this->FindPos(x);
    if (!IsActive(current_pos))
      return false;
    array_[current_pos].info_ = DELETED;
    --current_size_;
    return true;
  }
  
  // Return size of the table.
  size_t Size() const
  { return array_.size(); }
  
  // Return number of active elements in the table.
  size_t Num_Elements() const
  { return current_size_; }
  
  // Return total number of collisions that occurred in the table so far.
  int Num_Collisions() const
  { return num_collisions_; }
  
  // Set total number of collisions to 0.
  void Reset_Collisions()
  { num_collisions_ = 0; }

 protected:
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj & e = HashedObj{}, EntryType i = EMPTY)
    : element_{e}, info_{i} {}
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    : element_{std::move(e)}, info_{i} {}
  };
  
  std::vector<HashEntry> array_;
  size_t current_size_;
  mutable int num_collisions_;
  
  // Return true if element at @current_pos is active, false otherwise.
  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }
  
  // Return position that @x should be in by using hashing and probing.
  virtual size_t FindPos(const HashedObj & x) const {
    size_t offset = 1;   // Start at 1^2 == 1 for probing.
    size_t current_pos = InternalHash(x);
    while (array_[current_pos].info_ != EMPTY &&
           array_[current_pos].element_ != x) {
      ++num_collisions_;
      current_pos += offset;   // Compute ith probe.
      offset += 2;   // 1^2 + 3 = 2^2; 2^2 + 5 = 3^2; 3^2 + 7 = 4^2; ...
      if (current_pos >= array_.size())
        current_pos -= array_.size();   // Wrap around.
    }
    return current_pos;
  }
  
  // Double the size of the table and then rehash the elements.
  void Rehash() {
    std::vector<HashEntry> old_array = array_;
    // Create new double-sized, empty table.
    array_.resize(NextPrime(2 * old_array.size()));
    for (auto &entry : array_)
      entry.info_ = EMPTY;
    // Copy table over.
    current_size_ = 0;
    for (auto &entry : old_array)
      if (entry.info_ == ACTIVE)
        Insert(std::move(entry.element_));
  }
  
  // Hash function for the table using std:: default hash function.
  size_t InternalHash(const HashedObj & x) const {
    static std::hash<HashedObj> hf;
    return hf(x) % array_.size();
  }
};

#endif // QUADRATIC_PROBING_H
