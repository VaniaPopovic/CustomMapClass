#include "MyMap.h"
#include <algorithm>
#ifndef MYMAP_CPP
#define MYMAP_CPP

#pragma region MapOperations
//Constructor with no parameters
template <typename K, typename V>
MyMap<K, V>::MyMap()
{
	//initialize members to 0
	root = nullptr;
	_size = 0;
}

template <typename K, typename V>
MyMap<K, V>::~MyMap()
{//destructor
	//delete all elements of the tree and resets the size
	free_tree(root);
}

template <typename K, typename V>
//copy constructor with another map as parameter
MyMap<K, V>::MyMap(const MyMap& other)
{
	//constant iterators to instert values
	for (const_iterator it = other.cbegin(); it != other.cend(); ++it)
	{
		insert(it.first(), it.second());
	}
}

//equals operator overloading
template <typename K, typename V>
MyMap<K, V> MyMap<K, V>::operator=(const MyMap& other)
{
	//clears the map
	clear();
	//re intitialize it and return a reference to the map
	for (auto it = other.cbegin(); it != other.cend(); ++it)
	{
		insert(it.first(), it.second());
	}
	return *this;
}

//equals operator checking if two maps are equal
template <typename K, typename V>
bool MyMap<K, V>::operator==(const MyMap& other)
{
	auto it = other.cbegin();
	auto thisit = this->cbegin();
	for (it; it != other.cend(); ++it)
	{
		if (*it != *thisit)
		{
			//values are not equal
			return false;
		}
		++thisit;
	}
	if (it == other.cend() && thisit == cend())
	{
		//both iterators reached the end without returning false, map is equal
		return true;
	}
	else
	{
		//one map has more values than the other?
		return false;
	}
}

//not equal operator
template <typename K, typename V>
bool MyMap<K, V>::operator!=(const MyMap& other)
{
	return !(*this == other);
}

template<typename K, typename V>
V& MyMap<K, V>::operator[](K index)
{
	//returns a value reference to the pointer at index, not working correctly
	return *find(index);
}


template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::getRoot()
{
	//returns root, was used in debug
	return root;
}

template <typename K, typename V>
void MyMap<K, V>::Inorder(Node* root)
{
	//USED FOR DEBUG PURPOSES
	if (root == nullptr) return;

	Inorder(root->left);

	std::cout << root->value << std::endl;
	Inorder(root->right);
}

#pragma endregion
#pragma region Iterator

template <typename K, typename V>
MyMap<K, V>::iterator::iterator()
{
	//iterator empty constructor
	nodePTR = nullptr;
}

template <typename K, typename V>
inline MyMap<K, V>::iterator::iterator(Node* ptr)
{
	nodePTR = ptr;
}

template <typename K, typename V>
MyMap<K, V>::iterator::iterator(const iterator& it)
{
	//constructor with other node
	nodePTR = it.nodePTR;
}

template <typename K, typename V>
typename MyMap<K, V>::iterator& MyMap<K, V>::iterator::operator=(const iterator& it)
{
	nodePTR = it.nodePTR;
	return *this; //return the istance of the iterator
}

template <typename K, typename V>
inline bool MyMap<K, V>::iterator::operator==(const iterator& other) const
{
	return nodePTR == other.nodePTR;
	//check if they are equal
}

template <typename K, typename V>
inline bool MyMap<K, V>::iterator::operator!=(const iterator& other) const
{

	return !(*this == other);
}

template <typename K, typename V>
inline V MyMap<K, V>::iterator::operator*()
{
	//dereference operator for iterator
	return nodePTR->value;
}

template <typename K, typename V>
typename MyMap<K, V>::iterator& MyMap<K, V>::iterator::operator++()
{
	Node* currNode;

	if (nodePTR == nullptr)
	{
		nodePTR = nodePTR;
		if (nodePTR == nullptr)
			throw out_of_range();
		while (nodePTR->left != nullptr)
		{
			nodePTR = nodePTR->left;
		}
	}
	else if (nodePTR->right != nullptr)
	{
		nodePTR = nodePTR->right;
		while (nodePTR->left != nullptr)
		{
			nodePTR = nodePTR->left;
		}
	}
	else
	{
		currNode = nodePTR->parent;
		while (currNode != nullptr && nodePTR == currNode->right)
		{
			nodePTR = currNode;
			currNode = currNode->parent;
		}
		nodePTR = currNode;
	}
	return *this;
}

template <typename K, typename V>
inline typename MyMap<K, V>::iterator::iterator MyMap<K, V>::iterator::operator++(int)
{
	const iterator old(*this);
	++(*this);
	return old;
}

template <typename K, typename V>
typename MyMap<K, V>::iterator& MyMap<K, V>::iterator::operator--()
{
	if (nodePTR->left)
	{
		nodePTR = nodePTR->left;
		while (nodePTR->right)
		{
			nodePTR = nodePTR->right;
		}
	}
	else
	{
		Node* previous;
		do
		{
			previous = nodePTR;
			nodePTR = nodePTR->parent;
		}
		while (nodePTR == nodePTR->left && previous == nodePTR->left);
	}
	return *this;
}

template<typename K, typename V>
typename MyMap<K, V>::iterator MyMap<K, V>::iterator::operator--(int)
{
	iterator old(*this);
	--(*this);
	return old;
}

template <typename K, typename V>
inline const K& MyMap<K, V>::iterator::first()
{
	return nodePTR->key;
}

template <typename K, typename V>
inline V MyMap<K, V>::iterator::second()
{
	return nodePTR->value;
}
#pragma  endregion
#pragma region constantiterator
template <typename K, typename V>
MyMap<K, V>::const_iterator::const_iterator()
{
	nodePTR = nullptr;
}

template <typename K, typename V>
MyMap<K, V>::const_iterator::const_iterator(const Node* p)
{
	nodePTR = p;
}

template <typename K, typename V>
MyMap<K, V>::const_iterator::const_iterator(const const_iterator& it)
{
	nodePTR = it.nodePTR;
}

template <typename K, typename V>
MyMap<K, V>::const_iterator::const_iterator(const iterator& it)
{
	nodePTR = it.ptr;
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator& MyMap<K, V>::const_iterator::operator=(const const_iterator& it)
{
	nodePTR = it.nodePTR;
	return *this;
}

template <typename K, typename V>
bool MyMap<K, V>::const_iterator::operator==(const const_iterator& it) const
{
	return nodePTR == it.nodePTR;
}

template <typename K, typename V>
bool MyMap<K, V>::const_iterator::operator!=(const const_iterator& it) const
{
	return nodePTR != it.nodePTR;
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator& MyMap<K, V>::const_iterator::operator++()
{
	if (nodePTR->right)
	{
		nodePTR = nodePTR->right;
		while (nodePTR->left)
		{
			nodePTR = nodePTR->left;
		}
	}
	else
	{
		const Node* previous;
		do
		{
			previous = nodePTR;
			nodePTR = nodePTR->parent;
		}
		while (nodePTR && previous == nodePTR->right);
	}
	return *this;
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator MyMap<K, V>::const_iterator::operator++(int)
{
	const_iterator old(*this);
	++(*this);
	return old;
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator& MyMap<K, V>::const_iterator::operator--()
{
	if (nodePTR->left)
	{
		nodePTR = nodePTR->left;
		while (nodePTR->right)
		{
			nodePTR = nodePTR->right;
		}
	}
	else
	{
		const Node* previous;
		do
		{
			previous = nodePTR;
			nodePTR = nodePTR->parent;
		}
		while (nodePTR && previous == nodePTR->left);
	}
	return *this;
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator MyMap<K, V>::const_iterator::operator--(int)
{
	const_iterator old(*this);
	--(*this);
	return old;
}

template <typename K, typename V>
V MyMap<K, V>::const_iterator::operator*() const
{
	return (nodePTR->value);
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator MyMap<K, V>::begin() const
{
	//constant begin is same as cbegin
	return cbegin();
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator MyMap<K, V>::end() const
{
	//return cend
	return cend();
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator MyMap<K, V>::cbegin() const
{
	//find leftmost node - the first 
	Node* leftMost = root;
	if (root != nullptr)
	{
		if(root->left!=nullptr)
		{
			while (leftMost->left != nullptr)
			{
				leftMost = leftMost->left;
			}
		}
		return const_iterator(leftMost);
	}
	 return cend();
	
	//return node as type iterator
	
}

template <typename K, typename V>
typename MyMap<K, V>::const_iterator MyMap<K, V>::cend() const
{
	//after last element in map
	return const_iterator(nullptr);
}


#pragma endregion

#pragma region treeFunctions
template <typename K, typename V>
//initialisation list constructor for Node 
MyMap<K, V>::Node::Node(K k, V v, Node* p) : key(k), value(v), h(0), left(nullptr), right(nullptr), parent(p){}


template <typename K, typename V>
void MyMap<K, V>::checkImbalance(Node* n)
{
	setHeight(n);

	if (n->h == -2)
	{
		if (height(n->left->left) >= height(n->left->right))
			n = rotateRight(n);
		else
			n = doubleRotateLeft(n);
	}
	else if (n->h == 2)
	{
		if (height(n->right->right) >= height(n->right->left))
			n = rotateLeft(n);
		else
			n = doubleRotateRight(n);
	}

	if (n->parent != nullptr)
	{
		checkImbalance(n->parent);
	}
	else
	{
		root = n;
	}
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::rotateLeft(Node* a)
{
	//single left rotation
	Node* b = a->right;
	b->parent = a->parent;
	a->right = b->left;

	if (a->right != nullptr)
		a->right->parent = a;

	b->left = a;
	a->parent = b;

	if (b->parent != nullptr)
	{
		if (b->parent->right == a)
		{
			b->parent->right = b;
		}
		else
		{
			b->parent->left = b;
		}
	}

	setHeight(a);
	setHeight(b);
	return b;
}


template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::rotateRight(Node* a)
{

	//single right rotation
	Node* b = a->left;
	b->parent = a->parent;
	a->left = b->right;

	if (a->left != nullptr)
		a->left->parent = a;

	b->right = a;
	a->parent = b;

	if (b->parent != nullptr)
	{
		if (b->parent->right == a)
		{
			b->parent->right = b;
		}
		else
		{
			b->parent->left = b;
		}
	}

	setHeight(a);
	setHeight(b);
	return b;
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::doubleRotateLeft(Node* n)
{
	//double rotations http://btechsmartclass.com/DS/U5_T2.html
	n->left = rotateLeft(n->left);
	return rotateRight(n);
}

template <typename K, typename V>
typename MyMap<K, V>::Node* MyMap<K, V>::doubleRotateRight(Node* n)
{
	n->right = rotateRight(n->right);
	return rotateLeft(n);
}

template <typename K, typename V>
int MyMap<K, V>::height(Node* n)
{
	if (n == nullptr)
	{
		return -1;
	}
	return 1 + max(height(n->left), height(n->right));
}

template <typename K, typename V>
void MyMap<K, V>::setHeight(Node* n)
{
	//difference of height is between the rightsubtree and the left subtree
	n->h = height(n->right) - height(n->left);
}

#pragma endregion

#pragma region MapFunctions
template <typename K, typename V>
typename MyMap<K, V>::iterator MyMap<K, V>::begin()
{
	Node* leftMost = root;
	while (leftMost->left != nullptr)
	{
		leftMost = leftMost->left;
	}
	return iterator(leftMost);
}

template <typename K, typename V>
typename MyMap<K, V>::iterator MyMap<K, V>::end()
{
	return iterator(nullptr);
}

template <typename K, typename V>
bool MyMap<K, V>::insert(K key, V value)
{
	if (root == nullptr)
	{
		root = new Node(key, value, nullptr);
		_size++;
	}
	else
	{
		Node* n = root;
		Node* parent;

		while (true)
		{
			if (n->key == key)
				return false;

			parent = n;

			bool moveL = n->key > key;
			n = moveL ? n->left : n->right;

			if (n == nullptr)
			{
				if (moveL)
				{
					parent->left = new Node(key, value, parent);
					_size++;
				}
				else
				{
					parent->right = new Node(key, value, parent);
					_size++;
				}

				checkImbalance(parent);
				break;
			}
		}
	}

	return true;
}

template <typename K, typename V>
void MyMap<K, V>::erase(const K deleteKey)
{
	// no elements in the tree
	if (root == nullptr)
		return;

	Node* parent = root;
	Node* n = root;
	Node* child = root;
	Node* deleteNode = nullptr;
	

	while (child != nullptr)
	{
		parent = n;
		n = child;
		if(deleteKey >= n->key)
		{
			child = n->right;
		}
		else
		{
			child = n->left;
		}

		if (deleteKey == n->key)
			deleteNode = n;
	}

	if (deleteNode != nullptr)
	{
		//deleteNode->key = n->key;
		if(n->left !=nullptr)
		{
			child = n->left;
		}
		else child = n ->right;

		if (root->key == deleteKey)
		{
			root = child;
		}
		else
		{
			if (parent->left == n)
			{
				parent->left = child;
			}
			else
			{
				parent->right = child;
			}

			_size--;
			checkImbalance(parent);
		}
	}
}

template <typename K, typename V>
typename MyMap<K, V>::iterator MyMap<K, V>::find(const K key)
{
	Node* currNode = root;
	while (currNode)
	{
		//if key is found return iterator
		if (key == currNode->key)
		{
			return iterator(currNode);
		}
		//if it is smaller than current key move to the left of the subtree
		else if (key < currNode->key)
		{
			currNode = currNode->left;
		}
		//else move to the right
		else
		{
			currNode = currNode->right;
		}
		//key wasnt found return null ptr;
	}
	return end();
}

template <typename K, typename V>
typename MyMap<K, V>::iterator MyMap<K, V>::erase(iterator position)
{
	//call erase function with value
	erase(position.first());

	//should normally return iterator to position after the deleted value
	return iterator(nullptr);
}

template <typename K, typename V>
typename MyMap<K, V>::iterator MyMap<K, V>::erase(iterator first, iterator last)
{
	//deletes all elements in the range of first -last
	while (first != last)
	{
		iterator it = first;
		++first;
		erase(it);
	}
	//a
	erase(last);
	return iterator(nullptr);
}

template <typename K, typename V>
//simple getter for size
size_t MyMap<K, V>::size() const
{
	return _size;
}
// returns true or false depending if the size is 0
template <typename K, typename V>
bool MyMap<K, V>::empty() const noexcept
{
	return _size == 0 ? true : false;
}

//same as find but returns 0 and 1 instead of an iterator
template <typename K, typename V>
size_t MyMap<K, V>::count(const K k) const
{
	Node* currNode = root;
	while (currNode)
	{
		if (k == currNode->key)
		{
			return 1;
		}
		else if (k < currNode->key)
		{
			currNode = currNode->left;
		}
		else
		{
			currNode = currNode->right;
		}
	}
	return 0;
}
//same as find but it returns a value instead of an iterator or 0 and 1
template <typename K, typename V>
V MyMap<K, V>::at(const K k)
{
	return find(k, nullptr);
}

template <typename K, typename V>
//post order to delete all nodes (private method taking root as a pointer)
void MyMap<K, V>::free_tree(Node* node)
{
	if (node != nullptr)
	{
		free_tree(node->right);
		free_tree(node->left);
		free(node);
	}
}
//calls private method free_tree to delete all values
template <typename K, typename V>
void MyMap<K, V>::clear() noexcept
{
	free_tree(root);
	_size = 0;
	root = nullptr;
	//std::cout << "cleared";
}

template <typename K, typename V>
void MyMap<K, V>::swap(MyMap& other) noexcept
{
	//creates and stores a temp of this map instance
	const MyMap tmp(*this);
	//creates a temp2 that stores other instance
	const MyMap tmp2(other);
	this->clear(); //clears this map
	for (const_iterator it = tmp2.cbegin(); it != tmp2.cend(); ++it)
	{// add other map content to this map
		insert(it.first(), it.second());
	}
	other.clear();
	for (const_iterator it = tmp.cbegin(); it != tmp.cend(); ++it)
	{ //add this map content to other
		other.insert(it.first(), it.second());
	}

}


template <typename K, typename V>
int MyMap<K, V>::max(int a, int b)
{
	return ((a > b) ? a : b); //selfexplenatory 
}

template <typename K, typename V>
V MyMap<K, V>::find(K key, Node* p) //node*p is used to change the signature 
// this version of find returns values of the keys when found . usefull for at().
{
	Node* currNode = root;
	while (currNode)
	{
		if (key == currNode->key)
		{
			return currNode->value;
		}
		else if (key < currNode->key)
		{
			currNode = currNode->left;
		}
		else
		{
			currNode = currNode->right;
		}
	}
	throw out_of_range(); //throws outof range exception
}

template <typename K, typename V>
inline const K& MyMap<K, V>::const_iterator::first()
{
	return nodePTR->key;
}

template <typename K, typename V>
inline V MyMap<K, V>::const_iterator::second()
{
	return nodePTR->value;
}
#pragma endregion
#pragma region PersonClass
class person
{
public:
	int id;

	bool operator <(const person& rhs) const
	{
		return id < rhs.id;
	}

	bool operator >(const person& rhs) const
	{
		return id > rhs.id;
	}

	bool operator ==(const person& rhs) const
	{
		return id == rhs.id;
	}
};
#pragma endregion
#endif
