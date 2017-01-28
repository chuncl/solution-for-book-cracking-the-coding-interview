// return all subset of a set

#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

void printResult(vvi r) {
	for (size_t i = 0; i < r.size();  i++) {
		cout << " { ";
		for (size_t j = 0; j < r[i].size(); j++) {
			cout << " " << r[i][j];
		}
		cout << " } " << endl;
	}
}

/*
Recursion
starts from idx and add array[idx] value to previously 
got subset and add them to results
*/
void subsetR(const vi& a, int idx, vvi& subsets) {
	if (idx >= int(a.size())) {		
		subsets.push_back(vi());
	} else {
		subsetR(a, idx+1, subsets);
		// NOTE: we get size first as subsets are 
		// updated inside the loop!
		size_t s = subsets.size();
		for (size_t i = 0; i < s; i++) {
			vi v = subsets[i];
			v.push_back(a[idx]);
			subsets.push_back(v);
		}
	}
}

vvi subset(const vi& a) {
	vvi ret;
	subsetR(a, 0, ret);
	return ret;
}

/*
total 2^n power set
==> the ways of n bits
for {1 2 3} 
{ } ==> 000
{1} ==> 001
{1 2} ==> 011
*/
vvi subset2(const vi& a) {
	vvi subsets;
	size_t n = a.size();

	// n bits, not include max
	int max = 1 << n;	
	for (int i = 0; i < max; i++) {
		// convert int to subset based 
		// on its bit pattern
		int j = i;
		int idx = 0;
		vi subset;
		while (j) {
			if (j & 1) 
				subset.push_back(a[idx]);
			j >>=1;
			idx++;
		}
		subsets.push_back(subset);
	}

	return subsets;
}

int main() {
	int arr[] = {1, 2, 3, 4};
	vi a(arr, arr+sizeof(arr)/sizeof(int)) ;
	vvi ans = subset(a);
	printResult(ans);

	cout << "2nd approach" << endl;
	ans = subset2(a);
	printResult(ans);

	return 0;
}
