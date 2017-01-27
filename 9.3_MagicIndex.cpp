// a magic index means a[i] = i in an integer array. given a sorted distincted integer array, find magic index if any
// FOLLOW UP: what if integer array values are not distincted.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Note it is sorted integer array
like binary search to halve the search

as it is distinct, so if a middle element is less than its index, 
==>all left won't have migic index, as index less by one at left side, NOTE: it is the smallest difference between two distinct int
==>search right side.
similariy, if a middle element value is larger than its index, 
==> all right won't have magic index, as index increase by one, it is the smallest difference between two distinct int
==> search left side
*/
int magicIndexR(const vector<int>& a, int start, int end) {
	if (start > end || start < 0 || end > static_cast<int>(a.size()) - 1)
		return -1;
	int mid = (start + end) / 2;
	if (a[mid] == mid)
		return mid;
	else if (a[mid] < mid)
		return magicIndexR(a, mid + 1, end);
	else 
		return magicIndexR(a, start, mid-1);

}

/*
if a middle element is less than its index, as it is not distinct, 
==> so we can only skip left side value from (value, mid-1]
==>needs search two ranges
similarily for iddle element is larger than its index
*/
int magicIndexR2(const vector<int>& a, int start, int end) {
	if (start > end || start < 0 || end > static_cast<int>(a.size()) - 1)
		return -1;
	int mid = (start + end) / 2;
	if (a[mid] == mid)
		return mid;
	else if (a[mid] < mid) {
		int ans = magicIndexR2(a, start, a[mid]);
		if (ans != -1)
			return ans;
		else 
			return magicIndexR2(a, mid+1, end);
	}
	else {
		int ans = magicIndexR2(a, a[mid], end);
		if (ans != -1)
			return ans;
		else
			return magicIndexR2(a, start, mid-1);
	}
}

int main() {
	vector<int> a = { -10, -5, 0, 1, 2, 3, 4, 7, 10, 11, 12 };
	cout << magicIndexR(a, 0, a.size() - 1) << endl;
	a = { -10, -5, 2, 4, 5, 7, 8, 10, 11, 12, 13 };
	cout << magicIndexR(a, 0, a.size() - 1) << endl;

	a = { -10, -5, 0, 1, 2, 3, 4, 7, 10, 11, 12 };
	cout << magicIndexR2(a, 0, a.size() - 1) << endl;
	a = { -10, -5, 2, 4, 5, 7, 8, 10, 11, 12, 13 };
	cout << magicIndexR2(a, 0, a.size() - 1) << endl;

	a = { -10, -5, 2, 2, 3, 3, 4, 5, 6, 7, 8 };
	cout << magicIndexR2(a, 0, a.size() - 1) << endl;

	a = { -10, -5, 2, 4, 5, 7, 8, 9, 10, 10, 10 };
	cout << magicIndexR2(a, 0, a.size() - 1) << endl;

	return 0;
}