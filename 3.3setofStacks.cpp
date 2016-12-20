//Imagine a (literal) stack of plates. If the stack gets too high, it migh t topple. Therefore,
//in real life, we would likely start a new stack when the previous stack exceeds some
//threshold. Implement a data structure SetOfStacks that mimics this. SetOf-
//Stacks should be composed of several stacks and should create a new stack once
//the previous one exceeds capacity. SetOfStacks.push() and SetOfStacks.
//pop () should behave identically to a single stack (that is, pop () should return the
//same values as it would if there were just a single stack).
//FOLLOW UP
//Implement a function popAt(int index) which performs a pop operation on a
//specific sub-stack.

#include <iostream>
#include <vector>
#include <list>
#include <cassert>

const int STACK_SIZE = 2;
const int STATCK_NUM = 3;

class stack {
public:
	stack(int cap= STACK_SIZE) {
		buff.resize(cap);
		cur = -1;
		capacity = cap;
	}

	void push(int v) {
		if (full()) {
			throw std::exception("stack is full!");
		} 
		buff[++cur] = v;
	}

	int top() {
		if (empty()) {
			throw std::exception("stack is empty");
		}
		return buff[cur];
	}

	void pop() {
		if (empty()) {
			throw std::exception("stack is empty");
		}
		cur--;
	}

	size_t size() {
		return cur+1;
	}

	bool empty() {
		return cur == -1;
	}

	bool full() {
		return cur == capacity-1;
	}

private:
	std::vector<int> buff;
	int cur;
	int capacity;
};

class SetOfStacks {
public:
	SetOfStacks(int cap = STATCK_NUM) {   
		stacks = std::list<stack>(cap, stack(STACK_SIZE));
		cur = 0;
		capacity = cap;
	}

	void push(int v) {
		if (full()) {
			throw std::exception("stacks are full!");
		}
		stack& s = getStack(cur);
		if (!s.full()) {					
			s.push(v);				
		} else {
			stack& s2 = getStack(++cur);
			s2.push(v);
		}		
	}

	int top() {
		if (empty()) {
			throw std::exception("stacks are empty!");
		}

		stack& s = getStack(cur);
		if (!s.empty()) {		
			return s.top();		
		} else {
			stack& s2 = getStack(--cur);
			return s2.top();
		}		
	}

	void pop() {
		if (empty()) {
			throw std::exception("stacks are empty!");
		}

		stack& s = getStack(cur);
		if (!s.empty()) {		
			s.pop();		
		} else {
			stack& s2 = getStack(--cur);
			s2.pop();
		}		
	}

	bool empty() {
		if (cur == 0) {
			return getStack(cur).empty();
		} else {
			return false;
		}		
	}

	bool full() {
		if (cur == capacity-1) {
			return getStack(cur).full();
		} else {
			return false;
		}		
	}
private:
	stack& getStack(size_t idx) {
		assert(idx < stacks.size());
		std::list<stack>::iterator it = stacks.begin();
		advance(it,idx);
		return *it;
	}	 

private:
	std::list<stack> stacks;
	int cur;
	int capacity;
};

// with popAt
class SetOfStacks1 {
public:
	SetOfStacks1(int cap = STATCK_NUM) {   
		stacks = std::list<stack>(cap, stack(STACK_SIZE));
		cur = 0;
		capacity = cap;
	} 
	
	void push(int v) {
		if (full()) 
			throw std::exception("stacks are full!");
		stack* s = getStack(cur);
		if (s->full()) 					
			s = getStack(++cur);		
		s->push(v);				
	}

	int top() {
		if (empty()) 
			throw std::exception("stacks are empty!");
		stack* s = getStack(cur);
		while(s->empty()) {			
			s = getStack(--cur);
		}
		return s->top();		
	}

	void pop() {
		if (empty()) 
			throw std::exception("stacks are empty!");
		stack* s = getStack(cur);
		while(s->empty()) {			
			s = getStack(--cur);
		}
		s->pop();		
	}

	void popAt(int idx) {
		if (empty()) 
			throw std::exception("stacks are empty!");
		stack* s = getStack(idx);

		// it is possible that staring from idx, all stacks are empty, 
		// but overall stacks are not( e.g., some stacks after idx is not empty)
		while ((idx > -1) && s->empty()) 			
			s = getStack(--idx);
		
		if (idx <-1) 
			throw std::exception("stacks are empty!");

		s->pop();		
	}

	bool empty() {
		while((cur != -1) && getStack(cur)->empty())
			cur--;
		return (cur == -1);
	}

	bool full() {
		if (cur == capacity-1) {
			return getStack(cur)->full();
		} else {
			return false;
		}		
	}

private:
	stack* getStack(int idx) {
		assert(idx < stacks.size());		
		std::list<stack>::iterator it = stacks.begin();
		if (idx != -1)
			advance(it,idx);
		return &(*it);
}	 

private:
	std::list<stack> stacks;
	int cur;
	int capacity;
};

int main() {

	/*SetOfStacks s;
	for (int i = 0; i < 3*STACK_SIZE; i++) {
		s.push(i);
	}

	while(!s.empty()) {
		std::cout << s.top() << std::endl;
		s.pop();
	}*/


	SetOfStacks1 s;
	for (int i = 0; i < 3*STACK_SIZE; i++) {
		s.push(i);
	}

	for (int i = 0; i < STATCK_NUM; i++) {
		s.popAt(i);
	}

	while(!s.empty()) {
		std::cout << s.top() << std::endl;
		s.pop();
	}

	

	return 0;
}