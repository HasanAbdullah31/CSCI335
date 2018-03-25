// Hasan Abdullah: BinarySearchTree.h (09-30-2017)
// Changes made to this file were: internal insert methods call Merge() function
// from SequenceMap; public and internal contains methods; public and internal
// size() methods; public and internal totalHeight() methods; public find()
// method; and public and internal remove() methods.

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*****************************************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x, p )  --> Return true (and print x if bool p is true
//                        [default is false]) if x is present
// bool find( s, &r )     --> Return true if string s is found; r is set to
//                        the number of recursive calls used to try to find s
// bool remove( s, &r )   --> Return true if string s is found; r is set to
//                        the number of recursive calls used to try to remove s
// int totalHeight( )     --> Return sum of heights of all nodes
// size_t size( )         --> Return number of nodes
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS****************************************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree. Prints x if found and p is true.
     */
    bool contains( const Comparable & x, const bool & p = false ) const
    {
        return contains( x, root, p );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Returns true if s is found; r holds number of recursive calls done.
     */
    bool find( const string & s, int & r ) const
    {
        r = 0;   // initiate to 0 recursive calls
        Comparable x{ s, "foo" };   // constructor of SequenceMap
        return contains( x, root, r );
    }

    /**
     * Returns true if s is found; r holds number of recursive calls done
     * to try and remove the node containing s.
     */
    bool remove( const string & s, int & r )
    {
        r = 0;   // initiate to 0 recursive calls
        Comparable x{ s, "foo" };   // constructor of SequenceMap
        bool found = contains( x, root );
        remove( x, root, r );
	return found;
    }

    /**
     * Returns the sum of the heights of all nodes in the tree.
     */
    int totalHeight( ) const
    {
        if( isEmpty( ) )
            return 0;
        else
	{
	    int x = 0;   // need an lval for totalHeight(BinaryNode*, int&)
	    return totalHeight( root, x );
	}
    }

    /**
     * Returns the number of nodes in the tree.
     */
    size_t size( ) const
    {
        return size( root );
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; calls Merge( ) of SequenceMap on duplicates.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }

    /**
     * Insert x into the tree; calls Merge( ) of SequenceMap on duplicates.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Do nothing if x is not found.
     */
    void remove( const Comparable & x )
    {
        int r = 0;   // need an lval for remove(Comparable, BinaryNode* &, int&)
        remove( x, root, r );
    }

  private:
    struct BinaryNode
    {
        Comparable element;
	BinaryNode *left;
	BinaryNode *right;

	BinaryNode( const Comparable & theElement,
		    BinaryNode *lt, BinaryNode *rt )
	: element{ theElement }, left{ lt }, right{ rt } { }

        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
	: element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else   // This is part of Part2(a) of Homework 2
	    (t->element).Merge( x );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else   // This is part of Part2(a) of Homework 2
	    (t->element).Merge( x );
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * r tracks the number of recursive calls.
     */
    void remove( const Comparable & x, BinaryNode * & t, int & r )
    {
        ++r;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
	    remove( x, t->left, r );
        else if( t->element < x )
	    remove( x, t->right, r );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right, r );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     * print is optional flag; if print is true, x is cout'ed if found.
     */
    bool contains( const Comparable & x, BinaryNode *t,
		   const bool & print = false ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
	    return contains( x, t->left, print );
        else if( t->element < x )
	    return contains( x, t->right, print );
        else
	{   // The cout is part of Part2(a) of Homework 2
	    if( print )
	        cout << t->element << endl;
            return true;    // Match
	}
    }
    /**
     * Overloaded above; r tracks the number of recursive calls.
     */
    bool contains( const Comparable & x, BinaryNode *t, int & r ) const
    {
        ++r;
        if( t == nullptr )
            return false;
        else if( x < t->element )
	    return contains( x, t->left, r );
        else if( t->element < x )
	    return contains( x, t->right, r );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION************************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match
        return false;   // No match
    }
***************************************************************/

    /**
     * Internal method to find the sum of heights of all nodes in a subtree t;
     * num is the number of nodes in each subtree. Return the sum of heights.
     */
    int totalHeight( BinaryNode *t, int & num ) const
    {
        if( t == nullptr )
        {
	    num = 0;
	    return 0;
        }
	else
	{
	    num = 1;   // since t is not nullptr, it is 1 node
	    int left_num, right_num;   // number of nodes in left/right subtrees
	    int sum = totalHeight( t->left, left_num )
	            + totalHeight( t->right, right_num );
	    num += left_num + right_num;   // total number of nodes
	    // total height is (left height + right height == sum) + num - 1
	    return sum + num - 1;
	}
    }

    /**
     * Internal method to find the number of nodes in a subtree t.
     * Return the number of nodes.
     */
    size_t size( BinaryNode *t ) const
    {
        if( t == nullptr )
	    return 0;
        else
	    return size( t->left ) + size( t->right ) + 1;
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ),
		                   clone( t->right ) };
    }
};

#endif
