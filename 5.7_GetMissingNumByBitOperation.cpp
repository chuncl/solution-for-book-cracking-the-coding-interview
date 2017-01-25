// an array contains numbers from 0 - n. 1 number is missing. you cannot get integer as a whole in array, instead you can only get j bit of A[i]. find missing number in O(n)

#include <iostream>
#include <vector>
using namespace std;

// utility as mentioned in question, basic operation to get j bit of A[i]
int fetch(const vector<int>& A, int i, int j) {
	return (A[i] >> j) & 1;
}

// get array element/integer A[i] using the basic utility
int getElement(const vector<int>& A, int i) {
	int ret = 0;
	for (int j = 31; j >= 0; j--) {
		// NOTE: the commented out part is not right, as we don't want to shift right when j == 0;
		/*ret |= fetch(A, i, j);
		ret <<= 1;*/
		ret = (ret << 1) | fetch(A, i, j);
	}
	return ret;
}

// utility as mentioned in question, basic operation to get j bit of A
int fetch1(const vector<int>&A, int j) {
	return (A[j / 32] >> (j % 32)) & 1;
}

// get array element/integer A[i] using the basic utility
int getElement1(const vector<int>& A, int i) {
	int ret = 0;
	// NOTE: using "base" to simply the logic & thinking
	int base = 32 * i;
	for (int j = base + 31; j >= base; j--)
		ret = (ret << 1) | fetch1(A, j);
	return ret;
}

// use Hash to mark what is there, and then scan to get the missting one
// using O(n) of getElement, which is O(length of n) = O(logn), so total is 
// time complexity: O(nlogn)
int missing(const vector<int>& A) {
	vector<bool> hash(A.size() + 1);
	for (size_t i = 0; i < A.size(); i++) {
		/*int v = getElement(A, i);*/
		int v = getElement1(A, i);
		hash[v] = true;
	}

	for (size_t j = 0; j < hash.size(); j++) {
		if (!hash[j])
			return j;
	}

	return -1;
}

// utility as mentioned in question, basic operation to get j bit of A[i]
int fetch3(int v, int j) {
	return (v >> j) & 1;
}
/*
if n is odd ==> count(0) == count(1)
if n is even ==> count(0) == count(1)+1
set missing number as x
if x is odd ==> count(0) > count(1)
if x is even ==> count(0) <= count(1)

1. so based on counting the number of 0s/1s for each bit, we can know the bit value for missing x
2. after getting bit value for missing x, remove (ignore) all numbers that have different bit value, 
as when we getting to next bit, 
- the ones with the same bit value will form another smaller but the same question
- no missing in the numbers that have different bit value anyway
3. when getting empty list (no numbers left), which means count(0) <= count(1), so all 0s will be set to x
*/

void missing_R(const vector<int>& input, int col, int& v) {
	if (col > 31) {
		v = 0;
		return;
	}

	vector<int> zeros;
	vector<int> ones;
	for (size_t i = 0; i < input.size(); i++) {
		if (fetch3(input[i], col))
			ones.push_back(input[i]);
		else
			zeros.push_back(input[i]);
	}

	// recursively caculate other bits of v	
	// if v is odd ==> count(0) > count(1)
	// if v is even == > count(0) <= count(1)
	// adding 1 or 0 based on the count
	if (zeros.size() > ones.size()) {
		missing_R(ones, col + 1, v);
		v = (v << 1) | 1;
	}
	else {
		missing_R(zeros, col + 1, v);
		v = (v << 1) | 0;
	}
}

int missing2 (const vector<int>& A) {
	int ret = 0;
	missing_R(A, 0, ret);
	return ret;
}

int main() {
	vector<int> input = { 0,1,2,4,5,6,7,8,9,10 };
	cout << missing(input) << endl;
	cout << missing2(input) << endl;
}