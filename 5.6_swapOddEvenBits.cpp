// swap odd and even bits of a integer with a few instructions as possible

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

#define N sizeof(int)*8
#define min_int 1 << (N-1)
#define max_int ~(1 << (N-1))

string num_to_BinaryString(int v) {
	string ret;
	for (int i = 0; i < N; i++) {
		if (v & 1)
			ret += "1";
		else
			ret += "0";
		v >>= 1;
	}
	 reverse(ret.begin(), ret.end());
	 return ret;
}

int binaryString_to_num(const string& bs) {
	int ret = 0;
	assert(bs.length() <= N);
	for (size_t i = 0; i < bs.length(); ++i) {
		if (bs[i] != '1' && bs[i] != '0')
			assert("invalid inputs");
		if (bs[i] == '1')
			ret |= 1;			
		ret <<= 1;			
	}
	ret >>= 1;
	return ret;
}


// get odd bits ==> left shift
// right shift ==> get even bits
// |
// this is better than below in term of number of instructions
int swapBits(int x) {
	return ((x & 0x55555555) << 1) | ((x >> 1) & 0x55555555);
}

// get odd bits ==> left shift
// get even bits ==> right shift
// |
int swapBits1(int x) {
	return ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
}

int main() {

	string bs = "1111110010111100";
	int a = binaryString_to_num(bs);	

	int ar = swapBits(a);
	cout << num_to_BinaryString(ar) << endl;
	int ar1 = swapBits1(a);
	cout << num_to_BinaryString(ar1) << endl;

	string bs2 = "1100110010110101";
	int b = binaryString_to_num(bs2);	
	int br = swapBits(b);
	cout << num_to_BinaryString(br) << endl;
	int br1 = swapBits1(b);
	cout << num_to_BinaryString(br1) << endl;

	return 0;
}