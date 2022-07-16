#include <bits/stdc++.h>
#include <ctime>

using namespace std;


class Heap { // клас купи
private:
	int capacity; // ємність динамічного масиву
	int realSize; // кількість елементів у динамічному масиві
	const int alpha = 2; // load factor
	int* innerArray;

	void siftDown(int aIndex) { //  просіювання вниз для heapsort
		int leftChild = getLeftChild(aIndex);
		int rightChild = getRightChild(aIndex);

		int maxIndex = aIndex;

		if (leftChild < realSize && innerArray[maxIndex] < innerArray[leftChild]) { // якщо ліва дитина більша
			maxIndex = leftChild;
		}

		if (rightChild < realSize && innerArray[maxIndex] < innerArray[rightChild]) // якщо права дитина більша
			maxIndex = rightChild;

		if (maxIndex != aIndex) {
			swap(innerArray[maxIndex], innerArray[aIndex]);
			siftDown(maxIndex); // рекурсивна реалізація
		}
	}

	int getLeftChild(int aIndex) {
		return 2 * aIndex + 1;
	}

	int getRightChild(int aIndex) {
		return 2 * aIndex + 2;
	}
	int getParent(int aIndex) {
		return (aIndex - 1) / 2;
	}

public:
	Heap() { // конструктор для купи
		capacity = 1;
		realSize = 0;
		innerArray = new int[capacity]; // динамічне виділення пам'яті під масив
	}

	~Heap() { // деструктор для видалення динамічно виділеної пам'яті
		delete[] innerArray;
	}

	void push_back(int aObj) {
		if (capacity == realSize) { // немає куди додавати елементи
			capacity *= alpha;

			int* newArray = new int[capacity];
			
			for (int i = 0; i < realSize; i++) // перезапис елементів у масив більшої розмірності
				newArray[i] = innerArray[i];

			delete[] innerArray; // видалення старого масиву

			innerArray = newArray;

		}
		innerArray[realSize] = aObj;
		realSize++;
	}


	void heapSort() {
		for (int i = realSize - 1 / 2; i >= 0; i--) { // побудова max-heap
			siftDown(i);
		}
		
		int k = realSize;
		while(realSize != 0) { 
			swap(innerArray[realSize - 1], innerArray[0]); // обмін найбільшого елементу з останнім
			realSize--;
			siftDown(0); // просіювання елементу, з яким замінили найбільшого
		}
		realSize = k;
	}

	void print() {
		for (int i = 0; i < realSize; i++) {
			cout << innerArray[i] << ' ';
		}
		cout << endl;
	}
};




struct Node {
	int key;
	Node* left, *right;
};

class BST {
public:
	Node* root;
	int treeSize;
	vector<int> array; // масив для tree Sort
	BST() { // конструктор для бінарного дерева пошуку
		root = NULL;
		treeSize = 0;
	}
	~BST() { // деструктор для видалення динамічно виділеної пам'яті
		clear(root);
		array.clear();
	}

	void insert(const int& aKey) { // обгортка для додавання елементів
		root = insert(root, aKey);
	}

	bool search(const int& aKey) { // обгортка для пошуку елементів
		return search(root, aKey);
	}

	void treeSort() {

		Node *tempNode = NULL;
		tempNode = insert(tempNode, array[0]);
		for (int i = 1; i < array.size(); i++) {
			tempNode = insert(tempNode, array[i]); // побудова бінарного дерева пошуку з масиву array
		}
		root = tempNode;

		int i = 0;
		storeSorted(tempNode, i); // запис елементів у відсортованому порядку
	}

	void printBinTree(Node* aRoot, int aIndex) {
		if (aRoot != NULL) {

			printBinTree(aRoot->right, aIndex + 4);

			cout << setw(aIndex) << " " << aRoot->key << endl;
			printBinTree(aRoot->left, aIndex + 4);
		}
	}

private:

	Node* insert(Node* curNode, int aKey) {

		if (curNode == NULL) { // знайшлося місце для додавання елемента
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

	void storeSorted(Node* aNode, int &aIndex) {

		if (aNode != NULL) {
			storeSorted(aNode -> left, aIndex); // рекурсивне знахождення мінімального
			array[aIndex++] = aNode -> key; // запис до масиву елементу та збільшення індексу
			storeSorted(aNode -> right, aIndex);
		}
	}

	Node* search(Node* aRoot, int aKey) {
		if (aRoot == NULL || aRoot -> key == aKey) // елемент не знайдено або знайдено
			return aRoot;
			
		if (aKey < aRoot -> key)
			return search(aRoot -> left, aKey);
		
		return search(aRoot -> right, aKey);
	}

	void clear(Node* aRoot) { // рекурсивна реалізація очистки пам'яті для деструктора
		if (aRoot != NULL) {
			clear(aRoot -> left);
			delete aRoot;
			clear(aRoot -> right);
		}
	}

};


struct HufNode {
	char data;
	int freq;
	HufNode *left, *right;
	HufNode(char aData, int aFreq) { // конструктор для вузла дерева Хаффмана
		data = aData;
		freq = aFreq;
		left = right = NULL;
	}
};


class BitwiseWrite { // побітовий запис у файл
private:
	char buf;
	ostream& out;
	int totalBits;

public:
	BitwiseWrite(ostream & os) : out(os), buf(0), totalBits(0) { // очищення буферу та записаних бітів

  	}
	void flush();
	void writeBit(int aInteger);
};

void BitwiseWrite::flush() { 
	out.put(buf); // запис буферу до файлу
	out.flush(); // очищення буферу файлу
	totalBits = buf = 0;
}

void BitwiseWrite::writeBit(int aInteger) { // функція для перетворення бітів у байт та його запис

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

class BitwiseRead { // побітове читання з файлу
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

void BitwiseRead::fill() { // заповнення буферу байтом
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
	bool operator()(HufNode* fNode, HufNode* sNode) { // перевантаження оператора для порівняння
		return (fNode -> freq > sNode -> freq);
	}
};

void printCodes(HufNode* aRoot, string str, unordered_map<char, string>& aCharacterMap) {
	if (!aRoot)
		return;
	if (aRoot -> data != '^') { // якщо не спеціальний символ дерева
		aCharacterMap[aRoot-> data] = str;
		cout << aRoot -> data << ": " << str << endl;
	}
	
	printCodes(aRoot -> left, str + "0", aCharacterMap); // додаємо 0 до коду при проходженні ліворуч
	printCodes(aRoot -> right, str + "1", aCharacterMap); // додаємо 1 до коду при проходженні праворуч
}


void HuffmanCodes(map<char, int>& table, unordered_map<char, string>& aCharacterMap, priority_queue<HufNode*, vector<HufNode*>, comp>& aMinHeap) {
	int size = table.size();
	HufNode *left, *right, *top;

	//priority_queue<HufNode*, vector<HufNode*>, comp> minHeap;
	map<char, int>:: iterator itr;
	for (itr = table.begin(); itr != table.end(); itr++) {
		aMinHeap.push(new HufNode(itr -> first, itr -> second)); // додавання елементів в пріорітетну чергу
	}

	while (aMinHeap.size() != 0) {
		left = aMinHeap.top();
		aMinHeap.pop();
		right = aMinHeap.top();
		aMinHeap.pop();

		top = new HufNode('^', left -> freq + right -> freq); // побудова дерева Хаффмана

		top -> left = left;
		top -> right = right;
		aMinHeap.push(top);
	}
	printCodes(aMinHeap.top(), "", aCharacterMap); // обхід дерева для визначення кодів символів
}

char decode(BitwiseRead &in, priority_queue<HufNode*, vector<HufNode*>, comp>& aMinHeap, int& aHeader) { // декодування інформації для перевірки
	HufNode* temp = aMinHeap.top();
	int bit;
	while (true) {
		bit = in.readBit(); // побітове читання
		if (bit == 1)
			temp = temp -> right;
		if (bit == 0) {
			aHeader++; // перший байт 0 завжди у файлі
			temp = temp -> left;
		}
		if (temp -> right == NULL || temp -> left == NULL)
			break;
	}
	return temp -> data;
}

void printTree(ostream &out, HufNode* aRoot, int aIndex) { // виведення дерева Хаффмана
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
		char c; // вибір операції
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
				vector<int> numsToSort(sizeOfSortArray); // масив значень для сортування
				cout << "Enter your array: ";
				for (int i = 0; i < sizeOfSortArray; i++) {
					cin >> numsToSort[i];
				}

				if (temp == '1') {
					Heap heap;
					Heap testSpeedHeap; // купа для перевірки швидкості
					cout << "Do you want to test the speed of this algorithm on 100 000 elements? (y for YES, n for NO) ";
					char speed;
					cin >> speed;
					speed = tolower(speed);
					if (speed == 'y') {
						for (int i = 0; i <= 100'000; i++) {
							testSpeedHeap.push_back(rand() % 100'000 + 1);
						}
						clock_t start = clock();
						testSpeedHeap.heapSort();
						clock_t end = clock();
						float time = (float(end - start)) / CLOCKS_PER_SEC;
						cout << endl;
						cout << "The running time for HeapSort on 100 000 random elements is: ";
						cout << time << endl;
						cout << endl;
					}

					for (int i = 0; i < numsToSort.size(); i++)
						heap.push_back(numsToSort[i]);

					heap.heapSort();
					cout << "The sorted array using heapSort is: ";
					heap.print();
					cout << endl;
				}
				else if (temp == '2') {
					BST tree;
					BST testSpeedTree; // бінарне дерево пошуку для перевірки швидкості

					

					for (int i = 0; i < numsToSort.size(); i++)
						tree.array.push_back(numsToSort[i]);

					tree.treeSort();
					cout << "The sorted array using treeSort is: ";
					for (int i = 0; i < tree.array.size(); i++) {
						cout << tree.array[i] << ' '; // виведення відсортованого масиву
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
			string compressedFilename = filename; // перетворення формату у .cmp
			compressedFilename[length - 1] = 'p';
			compressedFilename[length - 2] = 'm';
			compressedFilename[length - 3] = 'c';


			ifstream F;
			map<char, int> frequency; // частота символів
			unordered_map<char, string> charBits; // символ та код

			F.open(filename);
			if (F) {
				while(true) {
					char tempForSymbols;
					F >> std::noskipws >> tempForSymbols; // читання посимвольно з пробілами

					if (F.eof()) {
						char eof = '#'; // символ кінця файлу для декодування
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

					string code = charBits[tempForFile]; // читання коду символу
					if (F.eof()) { 
						tempForFile = '#';
						code = charBits[tempForFile];
						for (int i = 0; i < code.size(); i++) {
							s.writeBit(code[i] - '0'); // якщо кінець файлу, додавання спеціального символу
						}
						break;
					}

					for (int i = 0; i < code.size(); i++) {
						s.writeBit(code[i] - '0');
					}

				}
				s.writeBit(-1); // завершення запису навіть якщо у буфері не 8 біт
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
					int header = 0; // для 8 бітів на початку
					while (true) {
						data = decode(file, minHeap, header); // перетворення бітів у символ
						if (header <= 8) // 8 бітів на початку 0
							continue;
						if (data == eof) {
							break;
						}
						ofs << data; // запис до файлу
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
			if (exitCondition == 'n') // Завершення роботи програми
				break;
	}
}