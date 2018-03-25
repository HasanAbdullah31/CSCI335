// Hasan Abdullah: BinaryHeap.h (11-22-2017)
// A binary heap with standard operations like insert() and deleteMin().

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "dsexceptions.h"
#include <vector>

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100) or a vector
//
// ******************PUBLIC OPERATIONS******************************************
// void insert( x )           --> Insert x
// Comparable deleteMin( )    --> Remove and return smallest item
// Comparable findMin( )      --> Return smallest item
// bool isEmpty( )            --> Return true if empty, else return false
// void makeEmpty( )          --> Remove all items
// ******************ERRORS*****************************************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 )
    : currentSize_{ 0 }, array_( capacity + 1 )
    {
    }

    explicit BinaryHeap( const std::vector<Comparable> & items )
    : currentSize_{ items.size( ) }, array_( items.size( ) + 10 )
    {
        for( int i = 0; i < items.size( ); ++i )
            array_[ i + 1 ] = items[ i ];
        buildHeap( );
    }

    bool isEmpty( ) const
    { return currentSize_ == 0; }

    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return array_[ 1 ];
    }

    /**
     * Insert item x, allowing duplicates.
     */
    void insert( const Comparable & x )
    {
        if( currentSize_ == array_.size( ) - 1 )
            array_.resize( array_.size( ) * 2 );
        // Percolate up
        int hole = ++currentSize_;
        Comparable copy = x;
        array_[ 0 ] = std::move( copy );
        for( ; x < array_[ hole / 2 ]; hole /= 2 )
            array_[ hole ] = std::move( array_[ hole / 2 ] );
        array_[ hole ] = std::move( array_[ 0 ] );
    }

    /**
     * Insert item x, allowing duplicates.
     */
    void insert( Comparable && x )
    {
        if( currentSize_ == array_.size( ) - 1 )
            array_.resize( array_.size( ) * 2 );
        // Percolate up
        int hole = ++currentSize_;
        for( ; hole > 1 && x < array_[ hole / 2 ]; hole /= 2 )
            array_[ hole ] = std::move( array_[ hole / 2 ] );
        array_[ hole ] = std::move( x );
    }

    /**
     * Remove the minimum item and return it.
     * Throws UnderflowException if empty.
     */
    Comparable deleteMin( )
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        Comparable minItem = std::move( array_[ 1 ] );
        array_[ 1 ] = std::move( array_[ currentSize_-- ] );
        percolateDown( 1 );
        return minItem;
    }

    void makeEmpty( )
    { currentSize_ = 0; }

  private:
    int currentSize_;                 // Number of elements in heap
    std::vector<Comparable> array_;   // The heap array

    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( )
    {
        for( int i = currentSize_ / 2; i > 0; --i )
            percolateDown( i );
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void percolateDown( int hole )
    {
        int child;
        Comparable tmp = std::move( array_[ hole ] );
        for( ; hole * 2 <= currentSize_; hole = child )
        {
            child = hole * 2;
            if( child != currentSize_ && array_[ child + 1 ] < array_[ child ] )
                ++child;
            if( array_[ child ] < tmp )
                array_[ hole ] = std::move( array_[ child ] );
            else
                break;
        }
        array_[ hole ] = std::move( tmp );
    }
};

#endif // BINARY_HEAP_H
