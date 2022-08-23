#pragma once
#include <vector>

struct Node {
	int key;
	Node* left, *right;
};

class BST {
	public:
		Node* root;
		int treeSize;
		std::vector<int> arr; // array for tree sort

		BST(); // constructor for Binary search tree
		~BST(); // destructor for deleting dynamically allocated memory
		void insert(const int& aKey); // wrapper for inserting elements
		bool search(const int& aKey); // wrapper for searching for elements
		void treeSort();
		void printBinTree(Node* aRoot, int aIndex);

	private:
		Node* insert(Node* curNode, int aKey);
		void storeSorted(Node* aNode, int &aIndex);
		Node* search(Node* aRoot, int aKey);
		void clear(Node* aRoot); // recursively deleting dynamically allocated memory
};