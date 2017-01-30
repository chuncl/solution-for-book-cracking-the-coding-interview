// Implement "paint fill" function. given a screen (2 dimentional array of colors), a point, and a new color, fill regions untill htiting the bondary of that color (original color) of the point

#include <iostream>
#include <vector>
using namespace std;

// NOTE: two dementional array representation
#define ROW 5
#define COL 5

// NOTE enum enumname {};
enum COLOR {red, yellow, blue, green};

// Make bound/valid check into a utility
bool isvalid(COLOR screen[][COL], int m, int n, COLOR c) {
	return (m >= 0 && m <= ROW && n >= 0 && n <= COL && screen[m][n] != c);
}

// DFS search essentially
void paintFill(COLOR screen[][COL], int m, int n, COLOR c) {
	if (!isvalid(screen, m, n, c))
		return;
	else {
		// NOTE this techinque to reduce code repetition, using static for light memory print
		static int rowNbr[] = { 0, -1, 0, 1};
		static int colNbr[] = { -1, 0, 1, 0};
		screen[m][n] = c;
		for (int i = 0; i < 4; i++) {
			paintFill(screen, m + rowNbr[i], n + colNbr[i], c);
		}
	}
}

void print(COLOR screen[][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			// C/C++ enum will print out enum integer value only
			cout << screen[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	COLOR s[][COL] = {
		{red, green, green, blue, yellow },
		{green, red, yellow, green, green},
		{green, green, red, blue, green},
		{red, green, green, green, yellow},
		{red, yellow, red, blue, yellow}	
	};

	paintFill(s, 1, 2, green);
	print(s);
	return 0;
}