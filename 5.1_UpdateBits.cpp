//You are given two 32 - bit numbers, N andM, and two bit positions, i and j.Write a method to insert M into Nsuch that M starts at bit j and
//ends at bit i.You can assume that the bits j through i have enough space to fit all ofM.That is, ifM = 10011, you can assume that there are at least 5 bits between j and i.
//You would not, for example, have j = 3 and i = 2, because M could not fully fit between bit 3 and bit 2.
//EXAMPLE:
//Input: N = 10000000000, M = 10011, i = 2, j = 6
//	Output : N = 10001001100

#include <iostream>
#include <vector>
using namespace std;

int updateBits(int n, int m, int i, int j) {

	// get mask like 11...10000011
	int left = ~0 << (j + 1);
	int right = (1 << i) - 1;
	int mask = left | right;

	// clear n with ask
	int ncleared = n & mask ;

	// shift m
	int mshift = m << i;

	// merge/put together
	return ncleared | mshift;
}

int updateBits2(int n, int m, int i, int j) {
	// store right part of n
	int right = (1 << i) - 1;
	int nright = n & right;

	// get left part of n
	// note this method: move left and then move right
	int nleft = (n >> (j + 1)) << (j + 1);

	// shift m
	int mshift = m << i;

	// merge/put togehter
	return nleft | nright | mshift;
}

void print_binary(int num)
{
	vector<int> ret;
	int mask = 1;
	int len = sizeof(int) * 8;
	while(len--) {
		if (num & mask)
			ret.push_back(1);
		else
			ret.push_back(0);

		mask <<= 1;
	}

	for (int i = ret.size()-1; i >=0; i--)
		cout << ret[i] << " ";

	cout << endl;
}

int main() {
	int N = 0x400;
	int M = 0x13;
	//int N = 1 << 10, M = 21;

	print_binary(N);
	print_binary(M);
	int i = 2, j = 6;
	int ret = updateBits(N, M, i, j);
	print_binary(ret);
	int ret2 = updateBits(N, M, i, j);
	print_binary(ret2);
}

//C++中关于位操作，记录几点需要注意的地方：
//
//一个有符号数，如果它的最高位为1，它右移若干位后到达位置i， 那么最高位到第i位之间全是1，例如：
//int a = 1;
//a <<= 31;	//a:1后面带31个0
//a >>= 31;	//a:32个1，即-1
//cout << a << endl;	//输出-1(写下负号，然后取反加1)
//一个无符号数，如果它的最高位为1，它右移若干位后到达位置i， 那么最高位到第i位之间全是0，例如：
//unsigned int a = 1;
//a <<= 31;	//a:1后面带31个0
//a >>= 31;	//a:31个0后面带一个1，即1
//cout << a << endl;	//输出1
//无论是有符号数还是无符号数，左移若干位后，原来最低位右边新出现的位全为0
//一个有符号的正数，它的最高位为0，如果因为左移使得最高位为1，那么它变为负数， 而后无论怎样右移，它都还是负数。除非因为再次左移使最高位变为0，那么它变回正数。
//int的最大值：~(1«31)，即0后面跟31个1
//int的最小值：1«31，即1后面跟31个0
//unsigned int最大值：~0，即32个1
//unsigned int最小值：0
//其它数据类型与int类似，只是位长不一样。