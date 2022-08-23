#include "BST.h"
#include <bits/stdc++.h>
//#include <ctime>

using namespace std;

BST::BST() { // constructor for Binary search tree
	root = NULL;
	treeSize = 0;
}

BST::~BST() { // destructor for deleting dynamically allocated memory
	clear(root);
	arr.clear();
}

void BST::insert(const int& aKey) { // wrapper for inserting elements
	root = insert(root, aKey);
}

bool BST::search(const int& aKey) { // wrapper for searching for elements
	return search(root, aKey);
}

void BST::treeSort() {

	Node *tempNode = NULL;
	tempNode = insert(tempNode, arr[0]);
	for (int i = 1; i < arr.size(); i++) {
		tempNode = insert(tempNode, arr[i]); // binary search tree creation using given array
	}
	root = tempNode;

	int i = 0;
	storeSorted(tempNode, i); // storing elements in ascending order
}

void BST::printBinTree(Node* aRoot, int aIndex) {
	if (aRoot != NULL) {

		printBinTree(aRoot->right, aIndex + 4);

		cout << setw(aIndex) << " " << aRoot->key << endl;
		printBinTree(aRoot->left, aIndex + 4);
	}
}

Node* BST::insert(Node* curNode, int aKey) {

	if (curNode == NULL) { // we are past leaf and can insert given element at the current position
		Node* newNode = new Node;
		newNode -> key = aKey;
		newNode -> right = newNode -> left = NULL;
		treeSize++;
		return newNode;
	}

	if (aKey < curNode -> key)
		curNode -> left = insert(curNode -> left, aKey);
	else 
		curNode -> right = insert(curNode -> right, aKey);

	return curNode;
}

void BST::storeSorted(Node* aNode, int &aIndex) {

	if (aNode != NULL) {
		storeSorted(aNode -> left, aIndex); // recursively finding the minimum element
		arr[aIndex++] = aNode -> key; // storing the found element and incrementing the position
		storeSorted(aNode -> right, aIndex);
	}
}

Node* BST::search(Node* aRoot, int aKey) {
	if (aRoot == NULL || aRoot -> key == aKey) // if element is either found or not found
		return aRoot;
			
	if (aKey < aRoot -> key)
		return search(aRoot -> left, aKey);
		
	return search(aRoot -> right, aKey);
}

void BST::clear(Node* aRoot) { // recursively deleting dynamically allocated memory
	if (aRoot != NULL) {
		clear(aRoot -> left);
		delete aRoot;
		clear(aRoot -> right);
	}
}