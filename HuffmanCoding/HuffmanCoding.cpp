#include "Heap.h"
#include "BST.h"
#include <bits/stdc++.h>
#include <ctime>

using namespace std;


struct HufNode {
	char data;
	int freq;
	HufNode *left, *right;
	HufNode(char aData, int aFreq) { // constructor for Huffman node
		data = aData;
		freq = aFreq;
		left = right = NULL;
	}
};


class BitwiseWrite { // bitwise writing in the file
private:
	char buf;
	ostream& out;
	int totalBits;

public:
	BitwiseWrite(ostream & os) : out(os), buf(0), totalBits(0) { // clearing the buffer and written bits

  	}
	void flush();
	void writeBit(int aInteger);
};

void BitwiseWrite::flush() { 
	out.put(buf); // writing buffer to the file
	out.flush(); // clearing the buffer
	totalBits = buf = 0;
}

void BitwiseWrite::writeBit(int aInteger) { // fuction for converting 8 bits into a byte and storing it

	if (aInteger == -1) {
		flush();
	}

	if (totalBits == 8) {
		flush();
	}

	unsigned char bitmask = 1;
	if (aInteger == 1) {
		bitmask = bitmask << (7 - totalBits);
		buf = buf | bitmask;
	}

	if (aInteger == 0) {
		bitmask = bitmask << (7 - totalBits);
		bitmask = ~bitmask;
		buf = buf & bitmask;
	}
	totalBits++;
}

class BitwiseRead { // bitwise reading from a file
private:
	char buf;
	istream& in;
	int totalBits;

public:
	BitwiseRead(istream& input);
	void fill();
	int readBit();
};

BitwiseRead::BitwiseRead(istream& input) : in(input) {
	buf = 0;
	totalBits = 0;
}

void BitwiseRead::fill() { // writing a byte into the buffer
	buf = in.get();
	totalBits = 0;
}

int BitwiseRead::readBit() {
	if (totalBits == 8)
    	fill();

	unsigned char bitmask = 1;
	bitmask = bitmask << (7 - totalBits); 
	bitmask = bitmask & buf;
	totalBits++;

	if (bitmask == 0)
		return 0;
	return 1;

}

struct comp {
	bool operator()(HufNode* fNode, HufNode* sNode) { // overloading operator for comparing Huffman nodes
		return (fNode -> freq > sNode -> freq);
	}
};

void printCodes(HufNode* aRoot, string str, unordered_map<char, string>& aCharacterMap) {
	if (!aRoot)
		return;
	if (aRoot -> data != '^') { // special symbol in the tree, meaning that it is a connection between two elements
		aCharacterMap[aRoot-> data] = str;
		cout << aRoot -> data << ": " << str << endl;
	}
	
	printCodes(aRoot -> left, str + "0", aCharacterMap); // adding 0 to the code when going left
	printCodes(aRoot -> right, str + "1", aCharacterMap); // adding 1 to the code when going right
}


void HuffmanCodes(map<char, int>& table, unordered_map<char, string>& aCharacterMap, priority_queue<HufNode*, vector<HufNode*>, comp>& aMinHeap) {
	int size = table.size();
	HufNode *left, *right, *top;

	//priority_queue<HufNode*, vector<HufNode*>, comp> minHeap;
	map<char, int>:: iterator itr;
	for (itr = table.begin(); itr != table.end(); itr++) {
		aMinHeap.push(new HufNode(itr -> first, itr -> second)); // adding elements to the priority queue
	}

	while (aMinHeap.size() != 0) {
		left = aMinHeap.top();
		aMinHeap.pop();
		right = aMinHeap.top();
		aMinHeap.pop();

		top = new HufNode('^', left -> freq + right -> freq); // creating a Huffman tree

		top -> left = left;
		top -> right = right;
		aMinHeap.push(top);
	}
	printCodes(aMinHeap.top(), "", aCharacterMap); // traversing through a Huffman tree to get codes
}

char decode(BitwiseRead &in, priority_queue<HufNode*, vector<HufNode*>, comp>& aMinHeap, int& aHeader) { // decoding information to check for correctness
	HufNode* temp = aMinHeap.top();
	int bit;
	while (true) {
		bit = in.readBit(); // bitwise reading
		if (bit == 1)
			temp = temp -> right;
		if (bit == 0) {
			aHeader++; // first byte 0 is always present in the file
			temp = temp -> left;
		}
		if (temp -> right == NULL || temp -> left == NULL)
			break;
	}
	return temp -> data;
}

void printTree(ostream &out, HufNode* aRoot, int aIndex) { // printing the Huffman tree
	if (aRoot != NULL) {


		printTree(out, aRoot->right, aIndex + 4);
		if (aRoot-> data == ' ')
			out << setw(aIndex) << " " << "Space" << endl;
		else if (aRoot->data == '\n')
			out << setw(aIndex) << " " << "EOL" << endl;

		out << setw(aIndex) << " " << (char)aRoot->data << endl;
		printTree(out, aRoot->left, aIndex + 4);
	}
}





int main() {
	srand(time(NULL));
	while(true) {
		cout << "Enter your operation: " << endl;
		cout << "1. Sorting elements" << endl;
		cout << "2. Searching for elements" << endl;
		cout << "3. Huffman encoding" << endl;
		char c; // chosing the operation
		cin >> c;

		char temp;
		if (c == '1') {
			while(true) {
				cout << "Choose the sorting algorithm: " << endl;
				cout << "1. HeapSort" << endl;
				cout << "2. TreeSort" << endl;
				cin >> temp;
				cout << "Enter the size of your array: ";
				int sizeOfSortArray;
				cin >> sizeOfSortArray;
				vector<int> numsToSort(sizeOfSortArray); // array of values for sorting
				cout << "Enter your array: ";
				for (int i = 0; i < sizeOfSortArray; i++) {
					cin >> numsToSort[i];
				}

				if (temp == '1') {
					Heap heap;
					Heap testSpeedHeap; // heap for testing runtime
					cout << "Do you want to test the speed of this algorithm on 100 000 elements? (y for YES, n for NO) ";
					char speed;
					cin >> speed;
					speed = tolower(speed);
					if (speed == 'y') {
						for (int i = 0; i <= 100'000; i++) {
							testSpeedHeap.push_back(rand() % 100'000 + 1);
						}
						clock_t start = clock();
						testSpeedHeap.heapsort();
						clock_t end = clock();
						float time = (float(end - start)) / CLOCKS_PER_SEC;
						cout << endl;
						cout << "The running time for HeapSort on 100 000 random elements is: ";
						cout << time << endl;
						cout << endl;
					}

					for (int i = 0; i < numsToSort.size(); i++)
						heap.push_back(numsToSort[i]);

					heap.heapsort();
					cout << "The sorted array using heapSort is: ";
					heap.print();
					cout << endl;
				}
				else if (temp == '2') {
					BST tree;
					BST testSpeedTree; // binary search tree for testing runtime

					

					for (int i = 0; i < numsToSort.size(); i++)
						tree.arr.push_back(numsToSort[i]);

					tree.treeSort();
					cout << "The sorted array using treeSort is: ";
					for (int i = 0; i < tree.arr.size(); i++) {
						cout << tree.arr[i] << ' '; // printing the sorted array
					}
					cout << endl;
					cout << "--------------------------------" << endl;
					cout << "The tree: " << endl;
					tree.printBinTree(tree.root, 0);
				}
				else
					cout << "Not a valid character" << endl;

				cout << "Do you want to continue doing this operation? (y for YES, n for NO): ";
				cin >> temp;
				temp = tolower(temp);
				if (temp == 'n')
					break;
			}
		}
		else if (c == '2') {
			BST tree;
			cout << "Enter the size of your array: ";
			int SizeOfFindArray;
			cin >> SizeOfFindArray;
			cout << "Enter your array: ";
			int tempNum;
			for (int i = 0; i < SizeOfFindArray; i++) {
				cin >> tempNum;
				tree.insert(tempNum);
			}
			while(true) {
				int elementToFind;
				cout << "Enter the element you want to find: ";
				cin >> elementToFind;
				if (tree.search(elementToFind)) {
					cout << endl;
					cout << "The element " << elementToFind << " has been found" << endl;
					cout << endl;
				}
				else
					cout << "No such element in the array" << endl;

				cout << "--------------------------------" << endl;
					cout << "The tree: " << endl;
					tree.printBinTree(tree.root, 0);

				cout << "Do you want to continue doing this operation on the same array? (y for YES, n for NO): ";
				cin >> temp;
				temp = tolower(temp);
				if (temp == 'n')
					break;
			}
		}
		else if (c == '3') {
			string filename;
			cout << "Enter the name of the file you want to compress: ";
			cin >> filename;

			int length = filename.size();
			string compressedFilename = filename; // changing the file format into .cmp
			compressedFilename[length - 1] = 'p';
			compressedFilename[length - 2] = 'm';
			compressedFilename[length - 3] = 'c';


			ifstream F;
			map<char, int> frequency; // frequency of the characters
			unordered_map<char, string> charBits; // symbol and its code

			F.open(filename);
			if (F) {
				while(true) {
					char tempForSymbols;
					F >> std::noskipws >> tempForSymbols; // reading symbol by symbol

					if (F.eof()) {
						char eof = '#'; // symbol of the end of the file
						frequency[eof] = 1;
						break;
					}

					if (frequency.find(tempForSymbols) == frequency.end()) {
						frequency[tempForSymbols] = 1;
					}
					else {
						frequency[tempForSymbols]++;
					}
				}
			}
			else {
				cout << "Can't open the file with the filename " << filename << endl;
			}
			F.close();
			ofstream File;
			File.open(compressedFilename, ios::binary);

			priority_queue<HufNode*, vector<HufNode*>, comp> minHeap;
			cout << "--------------------------------------------------" << endl;
			cout << "Codes for the characters: " << endl;
			HuffmanCodes(frequency, charBits, minHeap);
			cout << "--------------------------------------------------" << endl;
			cout << "Huffman tree:" << endl;
			printTree(cout, minHeap.top(), 0);
			cout << "--------------------------------------------------" << endl;

			F.open(filename);
			if (F) {
				BitwiseWrite s(File);
				cout << "Please, wait..." << endl;
				while (true) {
					char tempForFile;
					F >> std::noskipws >> tempForFile;

					string code = charBits[tempForFile]; // reading the code of the symbol
					if (F.eof()) { 
						tempForFile = '#';
						code = charBits[tempForFile];
						for (int i = 0; i < code.size(); i++) {
							s.writeBit(code[i] - '0'); // of the end of the file, add special symbol
						}
						break;
					}

					for (int i = 0; i < code.size(); i++) {
						s.writeBit(code[i] - '0');
					}

				}
				s.writeBit(-1); // ending the writing even if the buffer doesn't have 8 bits
				cout << "Encoding successfully finished!" << endl;
			}
			else {
				cout << "Can't open the file with a filename " << filename << endl;
			}
			
			File.close();
			F.close();
			char tempForDecode;
			cout << "Do you want to decode your file? (y for YES, n for NO): ";
			cin >> tempForDecode;
			tempForDecode = tolower(tempForDecode);
			if (tempForDecode == 'y') {
				ifstream F;
				F.open(compressedFilename, ios::binary);
				ofstream ofs;
				ofs.open("Decompressed.txt");
				BitwiseRead file(F);
				cout << "Please, wait..." << endl;
				if (F && ofs) {
					char data;
					char eof = '#';
					int header = 0; // for 8 bits on the start
					while (true) {
						data = decode(file, minHeap, header); // converting bits into a symbol
						if (header <= 8) // 8 bits are 0 in the beginning
							continue;
						if (data == eof) {
							break;
						}
						ofs << data; // writing to the file
					}
					cout << "Decompression finished successfully!" << endl;
				}
				else {
					cout << "Can't open the file" << endl;
				}
				F.close();
				ofs.close();
			}
		}
		else {
			cout << "Not a valid character" << endl;
		}

		char exitCondition;
		cout << "Do you want to choose another operation? (y for YES, n for NO): ";
		cin >> exitCondition;
		exitCondition = tolower(exitCondition);
			if (exitCondition == 'n') // the end of the program execution
				break;
	}
}