// Hasan Abdullah: DisjSets.h (11-22-2017)
// A union-find data structure (disjoint sets) with standard operations.

#ifndef DISJ_SETS_H
#define DISJ_SETS_H

// DisjSets class
//
// CONSTRUCTION: with int representing initial number of sets
//
// ******************PUBLIC OPERATIONS******************************************
// void unionSets( root1, root2 ) --> Merge two sets of roots root1 and root2
// bool isConnected(  )           --> Return true if all the elements are
//                                in one set, else return false
// bool isConnected( a, b )       --> Return true if element a is in the
//                                same set as element b, else return false
// int find( x )                  --> Return root of set containing x
// ******************ERRORS*****************************************************
// No error checking is performed

#include <vector>

/**
 * Disjoint sets class.
 * Use union by rank and path compression.
 * Elements in the set are numbered starting at 0.
 */
class DisjSets
{
  public:
    explicit DisjSets( int numElements );
    int find( int x ) const;
    int find( int x );
    bool isConnected(  ) const;
    bool isConnected( int a, int b ) const;
    void unionSets( int root1, int root2 );

  private:
    int numSets_;
    std::vector<int> s_;
};

#endif // DISJ_SETS_H
