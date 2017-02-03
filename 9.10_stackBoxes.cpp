// You have a stack of n boxes. box cannot be rotated and has width, length, and height. one box can be stacked on another box if and only if it is smaller in term of width, length, and height. 
// build tallest stack of boxes possible, where the height of stack is height of all boxes in that stack

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <string>

using namespace std;

struct Box {
	Box(double w = 0, double l = 0, double h = 0) : width(w), length(l), height(h) {}

	// NOTE: constness of both argument and method
	bool operator==(const Box& other) const {
		return width == other.width &&
			length == other.length &&
			height == other.height;
	}

	// NOTE: constness of both argument and method
	bool canBeAbove(const Box& other) const {
		return width < other.width &&
			length < other.length &&
			height < other.height;
	}

	double width;
	double length;
	double height;	
};

// Need functional for custom class as key for unordered_map (hash)
struct BoxHasher {
	size_t operator()(const Box& k) const {
		// NOTE how ot use hash fuction 
		// use to_string first
		// then XOR << 1, and then XOR >>1 of first result
		// boost::hash_combine is another alternative: http://stackoverflow.com/questions/19966041/getting-too-many-collisions-with-hash-combine
		hash<string> hashFuction;
		size_t t = hashFuction(to_string(k.width)) ^ (hashFuction(to_string(k.length)) << 1);
		return hashFuction(to_string(k.height)) ^ (t >> 1);
	}
};

/*
NOTE, if input boxes are vector, it is totally fine to use index as hash key. in this way, we dont' even borther to write hash function
https://codesolutiony.wordpress.com/category/cracking-the-coding-interview/
*/
typedef list<Box> LB;
typedef unordered_map<Box, LB, BoxHasher> MAP;
double getHeight(const LB& boxes) {
	double ret = 0;
	for (auto&b : boxes) {
		ret += b.height;
	}
	return ret;
}

/*
find the tallest stack with a particular as the base
use hahs to reduce duplicate calculation (memorization)
*/
LB subBoxR(const LB& boxes, Box base, MAP& M ) {
	if (M.find(base) != M.end())
		return M[base];

	LB result;
	LB maxPrev;
	double maxH = 0;
	// check all boxes, it will get to reduced sub-problems (and thus not infinite loop):
	// as canBeAbove will be false for itself and will take out all larger boxes ==> problem size becomes smaller
	// base case: for the smallest box as base, then maxPrev will be empty
	for (auto& b : boxes) {
		if (b.canBeAbove(base)) {
			LB prevLB = subBoxR(boxes, b, M);
			double h = getHeight(prevLB);
			if (h > maxH) {
				maxH = h;
				maxPrev = prevLB;
			}
		}
	}

	result.push_back(base);

	// check on base case: for the smallest box as base, then maxPrev will be empty
	/* This is why use list, instead of vector for perfromance consideration.*/
	// result. insert(result.end(), maxPrev.begin(), maxPrev。end()) will make copies, 
	// but splice won't, just transfer all elements from maxPrev to result and make it empty
	// list merge is for sorted list
	if (!maxPrev.empty()) {
		result.splice(result.end(), maxPrev);		
	}

	M[base] = result;
	return result;
}

/*
MAX(BOX1 as a bottom, BOX2 as a bottom and so on)
*/
LB stackBox(const LB& boxes) {
	MAP M;
	LB result;	
	double maxH = 0;
	for (auto &b : boxes) {
		LB aLB = subBoxR(boxes, b, M);
		double h = getHeight(aLB);
		if (h > maxH) {
			result = aLB;
		}
	}

	return result;
}

void print(const LB& boxes) {
	for (auto &b : boxes) {
		cout << " { " 
			<< b.width << " , "
			<< b.length << " , "
			<< b.height << " } ";
	}
	cout << endl;
}

int main() {
	LB boxes;
	boxes.push_back(Box(1, 1, 3));
	boxes.push_back(Box(2, 1, 4));
	boxes.push_back(Box(4, 2, 1));
	boxes.push_back(Box(6, 7, 7));

	LB r = stackBox(boxes);
	print(r);
	return 0;
}
