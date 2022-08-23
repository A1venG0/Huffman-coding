#pragma once
#include <iostream>

class BitwiseRead { // bitwise reading from a file
private:
	char buf;
	std::istream& in;
	int totalBits;

public:
	BitwiseRead(std::istream& input);
	void fill();
	int readBit();
};