#pragma once
#ifndef MYMAP_H
#define MYMAP_H

template <typename K, typename V>
class MyMap
{
public:
	struct Node //structure of the AVL tree 
	{
		K key; //Templated key - can take any type
		V value; //same for value
		int h; //AVL Tree height - holds a int number so we can later on check if it is balanced
		Node *left, *right, *parent; //pointers to traverse the tree
		Node(K k, V v, Node* p); //node constructor
	};

	MyMap(); //MyMap default constructor 
	MyMap(const MyMap& other); //copy Constructor 
	~MyMap(); //default constructor
	MyMap operator=(const MyMap& other); // e.g Map a= Map b; assigns values of other into the caller map.
	bool operator==(const MyMap& other); //checks if two maps are equal returns false and true
	bool operator!=(const MyMap& other); //checks inequality returns false and true
	V& operator[](K index); //subscript operator //TODO NOT IMPLEMENTED CORRECTLY

	class exception {}; 
	class out_of_range : public exception {}; //needed for at() when key not found

	//ITERATORS=====================================================================================

	class iterator
	{
	public:
		iterator(); //default contructor for iterator
		iterator(Node* ptr); //creating an iterator from a node pointer
		iterator(const iterator& it); //copy constructor
		iterator& operator=(const iterator& it); // assignment operator for two iterators
		bool operator==(const iterator& other) const; //equality operator for two iterators, needed for ranged for loops
		bool operator!=(const iterator& other) const; // inequality operator. needed for it.begin() != it.end()
		V operator*(); //dereference operator. Returns Value of a given iterator
		iterator& operator++(); //pre increament operator
		iterator operator++(int); //post incremeant
		iterator& operator--(); //pre decremeant
		iterator operator--(int); //post decreament
		const K& first(); //returns key of the Node pointed by the iterator
		V second(); //return value 

	private:
		Node* nodePTR; //Local reference to the node we are pointing
		friend class const_iterator; //const iterator can access iterators private and protected methods
	};



	class const_iterator
	{
	public: // pretty much the same as above but returns constant versions of the iterator
		const_iterator();
		const_iterator(const Node* p);
		const_iterator(const const_iterator& it);
		const_iterator(const iterator& it);
		const_iterator& operator=(const const_iterator& it);
		bool operator==(const const_iterator& it) const;
		bool operator!=(const const_iterator& it) const;
		const_iterator& operator++();
		const_iterator operator++(int);
		const_iterator& operator--();
		const_iterator operator--(int);
		const K& first();
		V operator*() const;
		V second();

	private:
		const Node* nodePTR;
	};


	const_iterator begin() const; //returns an costant iterator to the first (smallest key of the map)
	const_iterator end() const; //returns an costant iterator to the after the last (largest key of the map) -nullptr
	const_iterator cbegin() const; //same as const begin()
	const_iterator cend() const; //same as const  end()
	iterator begin(); //returns a normal iterator to the smallest value
	iterator end(); // returns normal iterator to the value after the last (After the last is a nullptr)
	bool insert(K key, V value); //insert a key value pair in the tree
	void erase(const K key); //erase key value pair from tree
	iterator erase(iterator position); //erase the key value pair pointed by the iterator
	iterator erase(iterator first, iterator last); //range erase from first to last
	iterator find(const K k); // find a key and return an iterator to the key value pair
	size_t size() const; //returns how many elements are in the map
	bool empty() const noexcept; //returns whether the map is empty or not
	size_t count(const K k) const; //counts how many keys are found in the map, must return 0 or 1 since map only support unique keys
	V at(const K k); //returns value of the Key or throws out_of_bounds if key is not in the map
	void clear() noexcept; //deletes all the keyvalue pairs in the map
	void swap(MyMap& other) noexcept; //swaps one map to another

private:

	int _size; //holds the amount of key value pairs in the map
	Node* root; //pointer to the root of the AVL Tree
	Node* getRoot(); //getter 
	void Inorder(Node* root); //debug purposes of printing of all nodes from smallest to biggest in the tree recursively
	Node* rotateRight(Node* a); // case when you need an RR rotation
	Node* rotateLeft(Node* a); //case when you need an LL rotation to balance the tree
	Node* doubleRotateRight(Node* n); //case when you need a LR
	Node* doubleRotateLeft(Node* n); //case when you need a RL
	int height(Node* n); //calculates the height of the node , returns -1 if given nullptr node
	void setHeight(Node* n); //sets the height of the nodes
	void checkImbalance(Node* n); //calculates the difference between the leaf nodes
	void free_tree(Node* node); //deletes recursively in post order the whole tree
	int max(int a, int b); //finds max value between two heights
	V find(K k, Node* p); //Private function used by at() to find a key and return the value

};
#endif
#include "MyMap.cpp"




