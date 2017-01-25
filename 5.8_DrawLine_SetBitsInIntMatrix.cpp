// A monochrome screen is stored as a single array of bytes, allowing eight consecutive pixels to be stored in one byte.The screen has width w, 
// where w is divisible by 8 (that is, no byte will be split across rows).The height of the screen, of course, can be derived from the length of the array 
// and the width.Implement a function drawHorizontalLine(byte[] screen, int width, intxl, intx2, inty) which draws a horizontal line from(x 1, y) to(x2, y).

#include <iostream>
#include <vector>
using namespace std;

/*
 basic apprach, loop through the bits and set bit one by one
*/
void drawHorizontalLine(unsigned char screen[], int sz, int width, int x1, int x2, int y) {
	for (int i = x1; i <= x2; i++) {
		int idx = (width * y + i) / 8;
		int bit = (width * y + i) % 8;
		int mask = 1 << (7 - bit);
		screen[idx] |= mask;
	}
}

/*
Optimized approach.

when x1 and x2 are far away, there are several byte blocks in between, mark/set byte block as a whole (for better performance)
use unsigned char to denote a byte and supporting bit operations

If you are using character types as numbers, use:
signed char, which gives you at least the -127 to 127 range. (-128 to 127 is common)
unsigned char, which gives you at least the 0 to 255 range.
*/

void drawHorizontalLine1(unsigned char screen[], int sz, int width, int x1, int x2, int y) {

	// get start byte block and offset
	int first_full_byte = x1 / 8;
	int start_offset = x1 % 8;
	if (start_offset != 0) {		
		first_full_byte++;
	}

	// get end byte block and offset
	int last_full_byte = x2 / 8;
	int end_offset = x2 % 8;
	if (end_offset != 7) {
		last_full_byte--;
	}

	// set byte block as a whole
	for (int i = first_full_byte; i <= last_full_byte; i++) {
		int byteIdx = width / 8 * y + i;
		screen[width / 8 * y + i] |= 0xFF;
	}

	// get start/end offset part's mask	
	unsigned char mask_start = 0xFF >> start_offset;
	unsigned char mask_end = 0xFF << (8- end_offset-1);

	// when x1  & x2 are in same byte block
	// AND the masks to set bits in between
	if (x1 / 8 == x2 / 8) {
		unsigned char mask = mask_start & mask_end;
		int byteIdx = width / 8 * y + x1 / 8;
		screen[byteIdx] |= mask;
	}
	else {
		// set start offset part if needed
		if (start_offset != 0) {
			unsigned char byteIdx = width / 8 * y + first_full_byte -1;
			screen[byteIdx] |= mask_start;
		}

		// set end offset part if needed
		if (end_offset != 7) {
			unsigned char byteIdx = width / 8 * y + last_full_byte + 1;
			screen[byteIdx] |= mask_end;
		}
	}
}

void printScreen(unsigned char screen[], int width, int height) {
	int byteWidth = width / 8;
	for (int r = 0; r < height; r++) {
		for (int c = 0; c < byteWidth; c++) {
			int idx = r*byteWidth + c;
			unsigned char v = screen[idx];
			// print bianary for a number
			for (int b = 7; b >= 0; b--) {
				if ((v >> b) & 1)
					cout << " 1 ";
				else
					cout << " 0 ";
			}
		}
		cout << endl;
	}		
}

int main() {
	unsigned char s[] = {
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
	};

	printScreen(s, 8*4, 8);

	// x at diffeferent byte block and there are byte blocks in between
	drawHorizontalLine(s, 4 * 8, 8*4, 4, 26, 2);
	cout << endl;
	printScreen(s, 8 * 4, 8);

	//// x at the same byte block
	//drawHorizontalLine(s, 4 * 8, 8 * 4, 9, 12, 2);
	//cout << endl;
	//printScreen(s, 8 * 4, 8);

	//// x at diffeferent byte block and there are NO byte blocks in between
	//drawHorizontalLine(s, 4 * 8, 8 * 4, 9, 17, 2);
	//cout << endl;
	//printScreen(s, 8 * 4, 8);


}