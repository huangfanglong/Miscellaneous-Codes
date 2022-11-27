/*
 * Long F. Huang (Z1942308)
 * Assignment 08
 * 11/1/2021
 * 
 * I certify that this is my own work and where appropriate an extension
 *  of the starter code provided for the assignment.
*/
#include "btree.h"

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public: 
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x
    
private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
};

//Public
template <typename T>
void BinarySearchTree<T>::Insert(const T &x)
{
	_Insert(this->root, x);
}

template <typename T>
bool BinarySearchTree<T>::Search(const T &x) const
{
	//call private _Search function and if the result is found, then return true
	//else return false
	_Search(this->root, x);
	if(_Search(this->root, x) == true)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

template <typename T>
bool BinarySearchTree<T>::Remove(const T &x)
{
	//call the public Search to see if the value exist within the tree and if it is a leaf
	//if it is true then remove
	Search(x);
	if(Search(x) == true)
	{
		_Remove(this->root, x);
		return true;
	}
	
	else
	{
		return false;
	}
}

//Private
template <typename T>
bool BinarySearchTree<T>::_Leaf(Node<T> *t) const
{
	//if both right and left has nothing, then is leaf
	if(t->left == NULL && t->right == NULL)
	{
		return true;
	}
	
	if(t == NULL)
	{
		return false;
	}
	//else is not
	else
	{
		return false;
	}
}

template <typename T>
void BinarySearchTree<T>::_Insert(Node<T> *&root, const T &x)
{
	//if the tree is empty, then the new node will be the root of the tree with the value x
	//and set both left and right to null (0)
    if(root == nullptr) 
    {
        root = new Node<T>(x, NULL, NULL);
    }
    
    //if x is less than root then insert left
    else if(x < root->data)
    {
        _Insert(root->left, x);
    }
    
    //if x is bigger than root then insert right
    else if(x > root->data)
    {
        _Insert(root->right, x);
    }
}

template <typename T>
bool BinarySearchTree<T>::_Search(Node<T> *t, const T &x) const
{
	//if root is not null
	if(t != nullptr)
	{
		//if data is x, then x is found && if it is leaf
		if(t->data == x && _Leaf(t) == true)
		{
			return true;
		}
		
		//if x is less than root, go search left recursively
		if(x < t->data)
		{
			_Search(t->left, x);
		}
		
		//else if x is bigger than root, go search right recursively
		else
		{
			_Search(t->right, x);
		}
	}

	else
	{
		return false;		
	}
}

template <typename T>
void BinarySearchTree<T>::_Remove(Node<T> *&t, const T &key)
{
	Node<T>* p = t;
	Node<T>* parent = nullptr;
	Node<T>* replace = nullptr;
	Node<T>* replace_parent = nullptr;
	while(p != nullptr && key != p->data)
	{
		parent = p;
		if(key < p->data)
		{
			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
		
	//case 1: no left child, replace p with right child
	if(p->left == nullptr)
	{
		replace = p->right;
	}
	//case 2: no right child, ...
	else if(p->right == nullptr)
	{
		replace = p->left;
	}
	//case 3: two children, replace p with inorder predecessor
	else
	{
		//go left
		replace_parent = p;
		replace = p->left;
		//then right
		while(replace->right != nullptr)
		{
			replace_parent = replace;
			replace = replace->right;
		}
		// If we were able to go to the right, make the replacement node's
        // left child the right child of its parent. Then make the left child
        // of p the replacement's left child.
        if(replace_parent != p)
        {
			replace_parent->right = replace->left;
			replace->left = p->left;
		}
		// Make the right child of p the replacement's right child.
		replace->right = p->right;
	}
	// Connect replacement node to the parent node of p (or the root if p has no parent).    
    if (parent == nullptr)
    {
		t = replace;
	}
	else
	{
		if(p->data < parent->data)
		{
			parent->left = replace;
		}
		else
		{
			parent->right = replace;
		}
	}
	// Delete the node.
	delete(p);
}

#endif // End of BINARYSEARCHTREE_H_
