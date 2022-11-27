/*
 * Long F. Huang (Z1942308)
 * Assignment 07
 * 10/25/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/
#include "node.h"
#include <iostream>

#ifndef H_BTREE
#define H_BTREE

template <typename T> 
class BinaryTree
{
public:
    BinaryTree() { root = NULL; };                     // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree
    
    typedef enum {left_side, right_side } SIDE;
	SIDE rnd()
	{ 
		return rand()%2 ? right_side : left_side;
	}

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

//Public
//call their private function counterparts
template <typename T>
unsigned BinaryTree<T>::getSize() const
{
	return _getSize(root);
}

template <typename T>
unsigned BinaryTree<T>::getHeight() const 
{
    return _getHeight(root);
}

template <typename T>
void BinaryTree<T>::Inorder(void (*move) (const T&)) 
{
    _Inorder(root, move);
}

template <typename T>
void BinaryTree<T>::Insert(const T& item) 
{
    _Insert(root, item);
}

//Private
template <typename T>
unsigned BinaryTree<T>::_getSize(Node<T> *node) const
{
	//Base case; if Node is null, then there is nothing. Return size 0.
	if(!node) { return 0; }
	//Recursive function to account for left and right nodes
	else
	{
		return _getSize(node->left) + _getSize(node->right) + 1;
	}
}

template <typename T>
unsigned BinaryTree<T>::_getHeight(Node<T> *node) const 
{
	//Base case; if Node is null, then there is nothing. Return size 0.
    if(!node) { return 0; }
	//Recursive function and max() to return the largest value of a and b
	//since height of a binary tree is equal to the highest(maximum) height.
	else
	{
		return 1 + max(_getHeight(node->left), _getHeight(node->right));
	}
}

template <typename T>
void BinaryTree<T>::_Insert(Node<T> *&node, const T& x) 
{
	//if the tree is empty, then the new node will be the root of the tree with the value x
    if(node == NULL) 
    {
        node = new Node<T>(x, NULL, NULL);
    }
    
    //otherwise, the left or the right subtree is randomly selected and 
	//the value x is inserted in that side
    else if(rnd() == right_side)
    {
        _Insert(node->right, x);
    }
    
    else
    {
        _Insert(node->left, x);
    }
}

template <typename T>
void BinaryTree<T>::_Inorder(Node<T>* node, void (*move) (const T&)) 
{
    if(node != NULL) 
    {
		//traverse through the left, then root(mid), then right of the tree until NULL
        _Inorder(node->left, move);
        move(node->data);
        _Inorder(node->right, move);
    }
    
    else { return; }
}
#endif // End of H_BTREE
