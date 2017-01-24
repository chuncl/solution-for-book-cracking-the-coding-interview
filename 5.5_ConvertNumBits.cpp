// determin number of bits required to convert integer A to integer B

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


int count_one(int x) 
{
	int c = 0;
	for (int i = 0; i < N; i++, x >>= 1) {
		if (x & 1)
			c++;
	}
	return c;
}

int count_one1(int x) {
	x =  (x & 0x55555555) + ((x >> 1) & 0x55555555);
	x =  (x & 0x33333333) + ((x >> 2) & 0x33333333);
	x =  (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
	x =  (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
	x =  (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
	return x;
}

int count_one2(int x) {
	int c = 0;
	for(; x !=0; x = x&(x-1), c++);
	return c;
}

// a^b's bits will be 
// - 1 if a and b's that particular bit is different
// - 0 if same
//==> so just count number of 1 bits in a^b will tell how many bits a have different from b
int bits_to_convert_num(int a, int b) {
	return count_one(a^b);
}

int main() {
	string bs = "0111110010111100";
	int num = binaryString_to_num(bs);
	cout << N << endl;
	cout << count_one(num) << endl;
	cout << count_one1(num) << endl;
	cout << count_one2(num) << endl;


	bs = "1111110010111100";
	num = binaryString_to_num(bs);	
	cout << count_one(num) << endl;
	cout << count_one1(num) << endl;
	cout << count_one2(num) << endl;

	cout << count_one(min_int) << endl;
	cout << count_one1(min_int) << endl;
	cout << count_one2(min_int) << endl;


	cout << count_one(max_int) << endl;
	cout << count_one1(max_int) << endl;
	cout << count_one2(max_int) << endl;

	bs = "1111110010111100";
	string bs2 = "1100110010110101";
	int a = binaryString_to_num(bs);	
	int b = binaryString_to_num(bs2);	
	cout << bits_to_convert_num(a, b) << endl;

	return 0;
}