// Hasan Abdullah: DisjSets.cc (11-22-2017)
// Implementation of disjoint sets with standard operations.

#include "DisjSets.h"

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */
DisjSets::DisjSets( int numElements )
: numSets_{ numElements }, s_( numElements, -1 )
{
}

/**
 * Union two disjoint sets.
 * Error checks omitted for simplicity.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */
void DisjSets::unionSets( int root1, int root2 )
{
    if( isConnected( root1, root2 ) )   // If in same set, no need to union
        return;
    if( s_[ root2 ] < s_[ root1 ] )   // root2 is deeper
        s_[ root1 ] = root2;          // Make root2 new root
    else
    {
        if( s_[ root1 ] == s_[ root2 ] )
            --s_[ root1 ];     // Update height if same
        s_[ root2 ] = root1;   // Make root1 new root
    }
    --numSets_;
}

/**
 * Return true if a and b are in the same set, else return false.
 */
bool DisjSets::isConnected( int a, int b ) const
{
    return find( a ) == find( b );
}

/**
 * Return true if all the elements are in one set, else return false.
 */
bool DisjSets::isConnected(  ) const
{
    return numSets_ == 1;
}

/**
 * Perform a find.
 * Error checks omitted again for simplicity.
 * Return root of the set containing x.
 */
int DisjSets::find( int x ) const
{
    if( s_[ x ] < 0 )
        return x;
    else
        return find( s_[ x ] );
}

/**
 * Perform a find with path compression.
 * Error checks omitted again for simplicity.
 * Return root of the set containing x.
 */
int DisjSets::find( int x )
{
    if( s_[ x ] < 0 )
        return x;
    else
        return s_[ x ] = find( s_[ x ] );
}
