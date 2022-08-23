#include "Heap.h"
#include <bits/stdc++.h>
//#include <ctime>

using namespace std;


void Heap::siftDown(int aIndex) { //  siftDown for heapsort
	int leftChild = getLeftChild(aIndex);
	int rightChild = getRightChild(aIndex);

	int maxIndex = aIndex;

	if (leftChild < realSize && innerArray[maxIndex] < innerArray[leftChild]) { // if the left child is bigger
		maxIndex = leftChild;
	}

	if (rightChild < realSize && innerArray[maxIndex] < innerArray[rightChild]) // if the right child is bigger
		maxIndex = rightChild;

	if (maxIndex != aIndex) {
		swap(innerArray[maxIndex], innerArray[aIndex]);
		Heap::siftDown(maxIndex); // recursive call
	}
}

int Heap::getLeftChild(int aIndex) {
	return 2 * aIndex + 1;
}

int Heap::getRightChild(int aIndex) {
	return 2 * aIndex + 2;
}

int Heap::getParent(int aIndex) {
	return (aIndex - 1) / 2;
}

Heap::Heap() { // heap constructor
	capacity = 1;
	realSize = 0;
	innerArray = new int[capacity]; // dynamic memory allocation for the array
}

Heap::~Heap() { // destructor for deleting dynamically alocated memory
	delete[] innerArray;
}

void Heap::push_back(int aObj) {
	if (capacity == realSize) { // if the array is full
		capacity *= alpha; // increase the capacity by load factor

		int* newArray = new int[capacity];
			
		for (int i = 0; i < realSize; i++) // rewrite the elements present in the array into the new array with bigger capacity
			newArray[i] = innerArray[i];

		delete[] innerArray; // delete the old array

		innerArray = newArray;

	}
	innerArray[realSize] = aObj;
	realSize++;
}

void Heap::print() {
	for (int i = 0; i < realSize; i++) {
		cout << innerArray[i] << ' ';
	}
	cout << endl;
}

void Heap::heapsort() {
	for (int i = realSize - 1 / 2; i >= 0; i--) { // max-heap creation
		Heap::siftDown(i);
	}
		
	int k = realSize;
	while(realSize != 0) { 
		swap(innerArray[realSize - 1], innerArray[0]); // swap the biggest element with the last one
		realSize--;
		Heap::siftDown(0); // sift down the last element on it's correct position
	}
	realSize = k;
}

