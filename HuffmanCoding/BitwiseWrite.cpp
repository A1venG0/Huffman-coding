#include "BitwiseWrite.h"
#include <iostream>

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