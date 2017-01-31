// Print all ways to arrange 8 queens on 8x8 chess board, so that no queens are at same row, same column or same diagonal.
#include <iostream>
using namespace std;

#define ROW 8
#define COL 8

void print(int c[]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (c[i] == j)
				cout << " 1 ";
			else
				cout << " 0 ";
		}
		cout << endl;
	}

	cout << endl;
}

/* Check if a position [r, c] is valid based on previous result cols[]
1. same column
2. diagonal
3. no need to check row, as the search algorithm recurse row by row
*/
bool isValid(int cols[], int r, int c) {
	for (int row = 0; row < r; row++) {
		// same column
		if (cols[row] == c)
			return false;
		// diagonal
		else if (abs(r - row) == abs(c - cols[row]))
			return false;
	}
	return true;
}

/*
1. use an array to store previous result, as only one queen on each row, no need matrix cols[i] = j means at row i queen is at column j 
2. recurse row by row, as each row only one queen allowed
3. for each row, check all possible columns to see if it is valid, if yes, put it in result cols[r], and recurse on next row
4. when getting to last row, print result and increment count. program will backtrack to get next valid solution
*/

void search(int cols[], int r, int& count) {
	// after finishing the last row, print the solution and increment count
	// NOTE: it is not r == ROW-1 as it is last row and needs to be processed below
	if (r == ROW) {
		print(cols);
		count++;
		return;
	}

	// for row r, check all possible columns
	for (int i = 0; i < COL; i++) {		
		if (isValid(cols, r, i)) {
			// if [r i] is valid (based on prevoius solution got so far), put it as part of the soution and recurse on next row
			cols[r] = i;
			search(cols, r + 1, count);
		}		
	}
}

int main() {
	int cols[ROW] = { -1, -1, -1, -1, -1 ,-1 ,-1 ,-1 };
	int count = 0;
	search(cols, 0, count);
	cout << count << endl;
	return 0; 
}