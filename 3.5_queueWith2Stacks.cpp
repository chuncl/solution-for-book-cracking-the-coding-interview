// implement MyQueue class with 2 stacks

#include <iostream>
#include <stack>

// whenever get value into queue, move stack sout to sin
// whenever, get value out of queue, move stack sin to sout
// move many times unessarilly, such as pop() and then pop() agan
template<typename T>
class MyQueue {
public:
	void push(const T& v) {
		moveStack(sout, sin);
		sin.push(v);
	}

	void pop() {
		moveStack(sin, sout);
		sout.pop();
	}

	T front() {
		moveStack(sin, sout);
		return sout.top();
	}

	T back() {
		moveStack(sout, sin);
		return sin.top();
	}

	size_t size() {
		return sin.size() + sout.size();
	}

	bool empty() {
		return sin.empty() && sout.empty();
	}


private:
	void moveStack(std::stack<T>& src, std::stack<T>& dst) {
		while(!src.empty()) {
			T v = src.top();
			src.pop();
			dst.push(v);
		}
	}

	std::stack<T> sin, sout;
};

// lazy approach
// whenever get value into queue, just push to old (1st) stack
// whenever, get value out of queue, if new (2nd) stack is not empty just get it; only move old(1st) stack to new (2nd) stack if it is empty
template<typename T> 
class MyQueue2 {
public:
	void push(const T& v) {
		sNew.push(v);
	}

	void pop() {
		moveStack(sNew, sOld);		
		sOld.pop();
	}

	T front() {
		moveStack(sNew, sOld);		
		return sOld.top();
	}

	T back() {
		moveStack(sOld, sNew);
		return sNew.top();
	}

	size_t size() {
		return sOld.size() + sNew.size();
	}

	bool empty() {
		return sOld.empty() && sNew.empty();
	}

private:
	void moveStack(std::stack<T>& src, std::stack<T>& dst) {
		// only move stack if destination stack is empty!
		if (dst.empty()) {
			while(!src.empty()) {			
				dst.push(src.top());
				src.pop();			
			}
		}
	}

	std::stack<T> sNew, sOld;
};


int main() {
	//MyQueue<int> q;
	MyQueue2<int> q;
	std::cout<< "empty? " << q.empty() << std::endl;
	for (int i = 0; i< 10; i++) {
		q.push(i);
	}
	std::cout<< "size " << q.size() << std::endl;
	std::cout<< "empty? " << q.empty() << std::endl;

	std::cout << "front " << q.front() << " back " << q.back() << std::endl;
	q.push(100);
	std::cout << "front " << q.front() << " back " << q.back() << std::endl;
	q.pop();
	std::cout << "front " << q.front() << " back " << q.back() << std::endl;
	return 0;
}