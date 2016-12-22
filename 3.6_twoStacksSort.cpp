//Write a program to sort a stack in ascending order (with biggest items on top).
//You may use at most one additional stack to hold items, but you may not copy the
//elements into any other data structure (such as an array). The stack supports the
//following operations: push, pop, peek, and isEmpty.

#include <iostream>
#include <stack>
#include <cstdlib>
#include <time.h>

// use an aditional stack
// 2 stacks mimic insert sort
void sort(std::stack<int>& s) {
	std::stack<int> t;
	while(!s.empty()) {
		int v = s.top();
		s.pop();
		while(!t.empty() && (t.top() > v)) {
			s.push(t.top());
			t.pop();
		}
		t.push(v);
	}

	while (!t.empty()) {
		s.push(t.top());
		t.pop();
	}
}

int main() 
{
	srand(unsigned(time(0)));
	std::stack<int> s;

	for (int i = 0; i < 10; i++) {
		s.push(rand()%100);
	}

	sort(s);

	while(!s.empty()) {
		std::cout <<s.top() << " " << std::endl;
		s.pop();
	}

	return 0;
}