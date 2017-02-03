// Given two sorted array A and B. A has enough space to hold B. write method to merge B into A as sorted array.

#include <iostream>
using namespace std;

/*
If start from front, then when we get a smaller value from B, we have to move all elements in array A back, not efficient
So we start from back
*/
void merge(int A[], int B[], int aSize, int bSize) {
	int idxMerge = aSize + bSize - 1;
	int idxA = aSize - 1;
	int idxB = bSize - 1;

	while (idxA >= 0 && idxB >= 0) {
		if (A[idxA] > B[idxB]) {
			A[idxMerge--] = A[idxA--];
		}
		else {
			A[idxMerge--] = B[idxB--];
		}
	}

	// No need to check on A, as if no elements in B left, then the rest A's elements are already in right places
	if (idxB >= 0) {
		A[idxMerge--] = B[idxB--];
	}
}

// one way to do swap, but not neccerily fast for moden compilers
void swap(int& a, int& b) {
	a = a^b;
	b = a^b;
	a = a^b;
}

// In place merge a array, where first halve and the 2nd halve are sorted
void merge_inplace(int A[], int start, int mid, int end) {
	for (int i = start; i <= mid; i++) {
		if (A[i] > A[mid + 1])
			swap(A[i], A[mid + 1]);		
		for (int j = mid + 1; j < end; j++) {
			if (A[j] <= A[j + 1])
				break;
			swap(A[j], A[j + 1]);
		}
	}
}

void print(int a[], int size) {
	for (int i = 0; i < size; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {
	int a[15] = { 1, 3, 7, 8, 9 };
	int b[] = { 2, 4, 5, 6, 10 };
	merge(a, b, 5, 5);
	print(a, 10);

	cout << "inplace merge" << endl;
	int c[10] = {
		8, 9, 11, 15, 17, 1, 3, 5, 12, 18
	};
	merge_inplace(c, 0, 4, 9);
	print(c, 10);

	return 0;
}