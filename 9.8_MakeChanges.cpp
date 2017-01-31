// given infinite quarers (25), dime (10), nickles(5) and cents (1), caculate number of ways to represent n cents

#include <iostream>
using namespace std;

/*
Recursion but there is DUPLICATE, such as 5, 1 and 1, 5, they shall be the same
KEY OBSERVATION: if they are ordered and put into set, then there will be no duplicates.
It would be tedious (and not optimal) to order the results, so 
==> can we enforce the order (big coin ==> small coin) during recursion? 
==> such that after we choose a 25, then valid coins are 25 10 5 0; if we choose 10, then valid coins are 10 5 1...etc..
==> in such way, we gurantee that one combination will be only count once
*/
int make_changeN(int n, int sum) {
	// invalid case
	if (sum > n)
		return 0;
	// base
	if (sum == n) 
		return 1;

	// recursion, but not ordered, as such there will be duplicates!
	return make_changeN(n, sum+25) +
		make_changeN(n, sum+10) +
		make_changeN(n, sum+5) +
		make_changeN(n, sum+1);
}

/*
==> can we enforce the order (big coin ==> small coin) during recursion? 
==> such that after we choose a 25, then valid coins are 25 10 5 0; if we choose 10, then valid coins are 10 5 1...etc..
==> in such way, we gurantee that one combination will be only count once
*/
int make_changeN2(int n, int sum, int coin) {
	int ways=0;
	// invalid case
	if (sum > n)
		return 0;
	// base case
	if (sum == n) 
		return 1;

	// Enforce the order (big coin ==> small coin) during recursion
	if (coin >= 25) 
		ways += make_changeN2(n, sum+25, 25);
	if (coin >= 10)
		ways += make_changeN2(n, sum+10, 10);
	if (coin >= 5)
		ways += make_changeN2(n, sum+5, 5);
	if (coin >= 1) 
		ways += make_changeN2(n, sum+1, 1);
	
	return ways;
}

/*
similar idea: keep order during recursion.
1: make change from big to small (order) 25 ==>10 ==> 5 ==>1
2. choose 0 - as many as we can for a coin (following order above)
3. 也是从币值大的硬币开始，每次取i个(i乘以币值要小于等于n)， 然后接着去取币值比它小的硬币，这时就是它的一个子问题了，递归调用。 具体来怎么来理解这个事呢？这样，
比如我要凑100分，那我先从25分开始， 我先取0个25分，然后递归调用去凑100分；再然后我取1个25分，然后递归调用去凑100-25 =75分；接着我取2个25分，递归调用去凑100-25*2=50分……这些取了若干个 
25分然后再去递归调用，取的就是10分了。一直这样操作下去，我们就会得到， 由若干个25，若干个10分，若干个5分和若干个1分组成的100分，而且， 这里面每种币值的数量都可以为0。
==>end up with a tree-like recursive structure where each call expands out to four or more calls
4 invalid cases are ruled out by conditon of for case. fully reduced cases are handled by "case 1"
*/
int make_changeN3(int n, int denom) {
	int ways = 0;
	int next_denom = 0;
	switch (denom) {
	case 25:
		next_denom = 10;
		break;
	case 10:
		next_denom = 5;
		break;
	case 5:
		next_denom = 1;
		break;
	case 1:
		return 1;
	}

	for (int i = 0; i*denom<=n; i++) {
		ways+= make_changeN3(n-i*denom, next_denom); 
	}

	return ways;
}

int main() {

	cout << make_changeN(10, 0) << endl;
	cout << make_changeN2(10, 0, 25) << endl;
	cout << make_changeN3(10, 25) << endl;
	return 0;
}