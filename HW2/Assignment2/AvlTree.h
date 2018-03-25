// Hasan Abdullah: AvlTree.h (09-30-2017)
// Changes made to this file were: internal insert methods call Merge() function
// from SequenceMap; public and internal contains methods; public and internal
// size() methods; public and internal totalHeight() methods; public find()
// method; and public and internal remove() methods.

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
using namespace std;

// AvlTree class
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
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    /**
     * Destructor for the tree
     */
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /**
     * Move assignment
     */
    AvlTree & operator=( AvlTree && rhs )
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
	    int x = 0;   // need an lval for totalHeight(AvlNode*, int&)
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
        int r = 0;   // need an lval for remove(Comparable, AvlNode* &, int&)
        remove( x, root, r );
    }

  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode    *left;
        AvlNode    *right;
        int        height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
        : element{ ele }, left{ lt }, right{ rt }, height{ h } { }

        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
        : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    AvlNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
	else   // This is part of Part2(a) of Homework 2
	    (t->element).Merge( x );
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else   // This is part of Part2(a) of Homework 2
	    (t->element).Merge( x );
        balance( t );
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     * r tracks the number of recursive calls.
     */
    void remove( const Comparable & x, AvlNode * & t, int & r )
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
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
        balance( t );
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t )
    {
        if( t == nullptr )
            return;
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const
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
    AvlNode * findMax( AvlNode *t ) const
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
    bool contains( const Comparable & x, AvlNode *t,
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
    bool contains( const Comparable & x, AvlNode *t, int & r ) const
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
    bool contains( const Comparable & x, AvlNode *t ) const
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
    int totalHeight( AvlNode *t, int & num ) const
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
    size_t size( AvlNode *t ) const
    {
        if( t == nullptr )
	    return 0;
        else
	    return size( t->left ) + size( t->right ) + 1;
    }

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t )
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
    void printTree( AvlNode *t ) const
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
    AvlNode * clone( AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ),
		                clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
