#include "BitwiseRead.h"
#include <iostream>

BitwiseRead::BitwiseRead(std::istream& input) : in(input) {
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