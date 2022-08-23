#pragma once

class Heap { // heap class
	private:
		int capacity; // size of the dynamic array
		int realSize; // number of elements in the dynamic array
		const int alpha = 2; // load factor
		int* innerArray;
		
		void siftDown(int aIndex);
		int getLeftChild(int aIndex);
		int getRightChild(int aIndex);
		int getParent(int aIndex);

	public:
		Heap();
		~Heap();
		void push_back(int aObj);
		void heapsort();
		void print();
};