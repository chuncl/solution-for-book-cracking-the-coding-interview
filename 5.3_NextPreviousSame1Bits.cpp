// Given a positive integer, print the next smallest and the next largest number that have the same number of 7 bits in their binary representation.

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

//https://en.wikipedia.org/wiki/Signed_number_representations
#define N sizeof(int)*8
#define max_int ~(1 << (N - 1)) // max int: 0111..111
#define min_int (1 << (N - 1)) //  min int: 1000..000

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

int count_one(int x) {
	int count = 0;
	for (int i = 0; i < N; i++) {
		if (x & 1)
			count++;
		x >>= 1;
	}
	return count;
}

int count_one2(int x) {
	x = (x & 0x55555555) + (x >> 1) & 0x55555555;
	x = (x & 0x33333333) + (x >> 2) & 0x33333333;
	x = (x & 0x0f0f0f0f) + (x >> 4) & 0x0f0f0f0f;
	x = (x & 0x00ff00ff) + (x >> 8) & 0x00ff00ff;
	x = (x & 0x0000ffff) + (x >> 16) & 0x0000ffff;
	return x;
}

int getNext(int x) {
	int c = count_one(x);

	// cannot find non-trailing 0s
	// e.g., 0000..0 OR 11111...111
	// AS we need "01" pattern	
	if (x == 0 || x == -1)
		return -1;
	
	// increment x until found a number with the same ones
	for (++x; count_one(x) != c && x < max_int; ++x);

	if (count_one(x) == c)
		return x;
	else
		// no such number, such as 
		// 0111..111 or 1111...1110
		return -1;
}

int getPrevious(int x) {
	int c = count_one(x);

	// cannot find non-trailing 1s
	// e.g., 0000..0 OR 11111...111
	// AS we need "10" pattern
	if (x == 0 || x == -1)
		return -1;

	// decrease x util found a number with the same ones
	for (--x; count_one(x) != c && x > min_int; --x);

	if (count_one(x) == c)
		return x;
	else
		// no such number, such as 
		// 0111..111
		return -1;
}

int getNext1(int x) {
	if (x == 0)
		return -1;

	int xx = x;
	int p = 0;

	// skip all trailing zeros if any
	for (; p < N && (x & 1) == 0; p++, x >>= 1);
	// skip all ones before that if any
	// stop at first "01" pattern appearing
	// p is index of this 0
	for (; p < N && (x & 1) == 1; p++, x >>= 1);

	// when p is at sign bit, such as 0100000..00, we cannot flip leading 0 with 1 as it will get to 
	// negative number, which is not next (bigger) number, similarily apply to any numbers like 01111...00
	// return -1 for this case ==> as -1 is 111111...11, no number that has the same number of 1s and either bigger or smaller, which makes sense to return -1
	if (p == N - 1)
		return -1;
	
	// flip 0 in 01 pattern
	x |= 1;
	
	// case such as 11100..00 ==> next smallest number 000...00111
	if (p == N)
		x = 0;

	// make trailing 1s as the number of the difference
	x <<= p;
	int diff1s = count_one(xx) - count_one(x);	
	int c = 1;
	for (; diff1s > 0; x |= c, c <<= 1, --diff1s);
	return x;		
}

int getPrevious1(int x) {
	if (x == 0)
		return -1;

	int xx = x;
	int p = 0;
	// skip all trailing ones if any
	for (; p < N && (x & 1) == 1; p++, x >>= 1);
	// skip all zeors before that
	// stop at the first 10 pattern appearing
	// p is index of 1
	for (; p < N && (x & 1) == 0; p++, x >>= 1);

	// when p is at sign bit, such as 10000..00, we cannot flip leading 1 to 0, as it will get to positive number, 
	// which is not previous (smaller) number. similiarily for any numbers like 10000011111
	// return -1
	if (p == N - 1)
		return -1;

	// flip 1 to 0
	x -= 1;

	// when no such pattern ("10") found, such as 0000011111 ==> previous largest number 11111000..00
	if (p == N)
		x = 0;

	// making leading 1s after p be the difference of 1s
	int diff1s = count_one(xx) - count_one(x);
	for (; diff1s > 0; x = (x << 1) | 1, --diff1s, --p);
	x <<= p;
	return x;
}

int getNext2(int x) {
	if (x == 0)
		return -1;
	
	// count number of trailing zeros
	// count number of 1s before trailing zeros
	int xx = x;
	int c0 = 0;
	int c1 = 0;

	while ((xx & 1) == 0) {
		c0++;
		xx >>= 1;
	}
	while ((xx & 1) == 1) {
		c1++;
		xx >>= 1;
	}
	// when p = c0 + c1 is at sign bit, such as 0100000..00, we cannot flip leading 0 with 1 as it will get to 
	// negative number, which is not next (bigger) number, similarily apply to any numbers like 01111...00
	// return -1 for this case 
	int p = c0 + c1;
	if (p == N - 1)
		return -1;
	
	// flip p (10 pattern, index of 1)
	x |= (1 << p);
	// clear all bits after p
	x &= ~((1 << p) - 1);
	// set LSBs for 1s, number of c1-1, as 1 has been used to flip p above
	x |= (1 << (c1-1)) - 1;
	return x;
}

int getPrevious2(int x) {
	if (x == 0)
		return -1;

	// count number of trailing ones
	// count number of 0s before trailing zeros
	int xx = x;
	int c0 = 0;
	int c1 = 0;

	while ((xx & 1) == 1) {
		c1++;
		xx >>= 1;
	}
	while ((xx & 1) == 0) {
		c0++;
		xx >>= 1;
	}

	// when p is at sign bit, such as 10000..00, we cannot flip leading 1 to 0, as it will get to positive number, 
	// which is not previous (smaller) number. similiarily for any numbers like 10000011111
	// return -1
	int p = c0 + c1;
	if (p == N - 1)
		return -1;
	
	int m = ~0 << (p + 1);
	x &= m;
	int n = (1 << (c1 + 1)) - 1;
	n <<= c0-1;
	x |= n;
	return x;

}

int main() {
	//cout << N << endl;
	//cout << num_to_BinaryString(-1) << endl;
	//cout << num_to_BinaryString(min_int) << endl;
	//cout << num_to_BinaryString(17) << endl;
	//cout << count_one(17) << endl;
	//cout << count_one2(17) << endl;

	string bs("11011001111100");
	int num = binaryString_to_num(bs);
	cout << num << " Input binary: " << num_to_BinaryString(num) << endl;
	int next = getNext(num);
	cout << next << " Next  binary: " << num_to_BinaryString(next) << endl;
	int previous = getPrevious(num);
	cout << previous << " Prev  binary: " << num_to_BinaryString(previous) << endl;

	cout << num << " Input binary: " << num_to_BinaryString(num) << endl;
	next = getNext1(num);
	cout << next << " Next  binary: " << num_to_BinaryString(next) << endl;
	previous = getPrevious1(num);
	cout << previous << " Prev  binary: " << num_to_BinaryString(previous) << endl;


	cout << num << " Input binary: " << num_to_BinaryString(num) << endl;
	next = getNext2(num);
	cout << next << " Next  binary: " << num_to_BinaryString(next) << endl;
	previous = getPrevious2(num);
	cout << previous << " Prev  binary: " << num_to_BinaryString(previous) << endl;

/*
	int a = (1 << 31) + (1 << 29);
	cout << a << " Input binary: " << num_to_BinaryString(a) << endl;
	int next = getNext(a);
	cout << next << " Next Binary: " << num_to_BinaryString(next) << endl;
	int previous = getPrevious(a);
	cout << previous << " Prevoius Binary: " << num_to_BinaryString(previous) << endl;*/

	return 0;
}