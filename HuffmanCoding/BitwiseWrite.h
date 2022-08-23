#pragma once
#include <iostream>

class BitwiseWrite { // bitwise writing in the file
private:
	char buf;
	std::ostream& out;
	int totalBits;

public:
	BitwiseWrite(std::ostream & os) : out(os), buf(0), totalBits(0) { // clearing the buffer and written bits

  	}
	void flush();
	void writeBit(int aInteger);
};