// implement a stack with operation push, pop and min, all O(1) time

#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <algorithm>

// each node has extra field to record minnimum seen so far
struct node {
	node(int v, int m) : value(v), min(m) {}
	int value;
	int min;
};

class minStack {
public:
	void push(int v) {
		int m = std::min(v, min());
		s.push(node(v, m));
	}

	void pop() {
		s.pop();
	}	

	int min() {
		if (s.empty()) {
			return INT_MAX;
		}
		else {
			node n = s.top();
			return n.min;
		}
	}

	void init(std::vector<int> arr) {
		for (size_t i = 0; i < arr.size(); i++)
			push(arr[i]);
	}

private:
	std::stack<node> s;
};

// use 2 stacks, the 2nd stack record the minimum seen so far
// potentailly save space, e.g., only one element in the 2nd stack when pushing 1, 2 ...1000 in stack
class minStack2 {
public:
	void push(int v) {
		if (v <= min())
			sMin.push(v);
		s.push(v);
	}

	int min() {
		if (sMin.empty()) {
			return INT_MAX;
		}

		return sMin.top();
	}

	void pop() {
		if (s.top() == sMin.top()) {
			sMin.pop();
		}
		s.pop();
	}

	void init(std::vector<int> arr) {
		for (size_t i = 0; i < arr.size(); i++)
			push(arr[i]);
	}

private:
	std::stack<int> s;
	std::stack<int> sMin;
};


int main() {	
	/*std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };
	minStack s;
	s.init(arr);
	std::cout << s.min() << std::endl;
	s.pop();
	std::cout << s.min() << std::endl;	
	
	std::vector<int> arr2 = { 5, 6, 3, 7};
	minStack s2;
	s2.init(arr2);
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;*/

	std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7 };
	minStack2 s;
	s.init(arr);
	std::cout << s.min() << std::endl;
	s.pop();
	std::cout << s.min() << std::endl;

	std::vector<int> arr2 = { 5, 6, 3, 7 };
	minStack2 s2;
	s2.init(arr2);
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;
	s2.pop();
	std::cout << s2.min() << std::endl;

	return 0;
}