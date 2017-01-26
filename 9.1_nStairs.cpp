// n stairs, kid can hop 1/2/3/ steps. how many way kid can get up the stairs

#include <iostream>
#include <unordered_map>
using namespace std;

// O(n^3)
// use long long 
// and map as hash, as vector's index is size_t
typedef long long ll;
typedef unordered_map<int, ll> HASH;

ll count(int n, HASH& map) {
	// note base condition
	// n < 0 ==> invalid, dosn't count, as such return 0
	// n ==0 ==> a valid one, count as 1
	if (n <0)
		return 0;
	else if (n == 0)
		return 1;
	// memorization to speed up
	else if (map.find(n) != map.end()) 
		return map[n];
	else {
		// recurse & update hash
		ll ret = count(n-1, map) + count(n-2, map) + count(n-3, map);
		map[n] = ret;
		return ret;
	}
}

int main() {
	HASH m;
	cout << count(3, m) << endl;
	cout << count(10,m) << endl;
}