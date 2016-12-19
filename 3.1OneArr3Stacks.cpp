// use signle array to implement three stacks

#include <iostream>
#include <vector>
#include <exception>
#include <cassert>

// fixed size
class threeStacks {
public:
	threeStacks(int sz = 100) {
		_size = sz;
		_buff.resize(3 * _size);
		_ptops[0] = _ptops[1] = _ptops[2] = -1;
	}

	void push(int stackNum, int v) {
		if (isFull(stackNum)) {
			throw std::exception("stack is full");
		}
		int idx = stackNum*_size + _ptops[stackNum] + 1;
		_buff[idx] = v;
		_ptops[stackNum]++;	
	}

	bool empty(int stackNum) {
		return _ptops[stackNum] == -1;
	}

	int top(int stackNum) {
		if (empty(stackNum)) {
			throw std::exception("stack is empty");
		}
		int idx = stackNum*_size + _ptops[stackNum];
		return _buff[idx];
	}

	void pop(int stackNum) {
		if (empty(stackNum)) {
			throw std::exception("stack is empty");
		}
		_ptops[stackNum]--;
	}

	size_t size(int stackNum) {
		return _ptops[stackNum] + 1;
	}
private:	
	bool isFull(int stackNum) {
		return _ptops[stackNum] == _size - 1;
	}

private:
	std::vector<int> _buff;
	int _ptops[3]; // relative value for each stack
	int _size;
};

// push consequently into array, need maintain previous node idex of a stack
struct node {
	node(int v=0, int pidx=-1) : value(v), preIdx(pidx) {}
	int value, preIdx;
};

class threeStacks1 {
public:
	threeStacks1(int tsz =100) {
		_buff.resize(tsz);
		_ptops[0] = _ptops[1] = _ptops[2] = -1;
		_totalSize = tsz;
		_cur = 0;
	}

	void push(int stackNum, int v) {
		if (_cur == _totalSize - 1) {
			throw std::exception("stack is full");
		}
		_buff[_cur] = node(v, _ptops[stackNum]);
		_ptops[stackNum] = _cur++;
	}

	bool empty(int stackNum) {
		return _ptops[stackNum] == -1;
	}

	int top(int stackNum) {
		if (empty(stackNum)) {
			throw std::exception("stack is empty");
		}
		return _buff[_ptops[stackNum]].value;
	}

	void pop(int stackNum) {
		if (empty(stackNum)) {
			throw std::exception("stack is empty");
		}
		_ptops[stackNum] = _buff[_ptops[stackNum]].preIdx;
	}

	size_t size(int stackNum) {
		int idx = _ptops[stackNum];
		if (idx == -1) {
			return 0;
		}
		else {
			size_t sz(1);
			while (_buff[idx].preIdx != -1) {
				sz++;
				idx = _buff[idx].preIdx;
			}
			return sz;
		}	
	}
private:
	std::vector<node> _buff;
	int _ptops[3];
	int _totalSize;
	size_t _cur;
};

// add logic in push and pop to re-use poped elements
class threeStacks2 {
public:
	threeStacks2(int tsz = 100) {
		_buff.resize(tsz);
		_ptops[0] = _ptops[1] = _ptops[2] = -1;
		_totalSize = tsz;
		_cur = 0;
	}

	void push(int stackNum, int v) {
		if (_cur == _totalSize - 1) {
			throw std::exception("stack is full");
		}
		_buff[_cur] = node(v, _ptops[stackNum]);
		_ptops[stackNum] = _cur++;	
		while (_buff[_cur].preIdx != -1) {
			_cur++;
		}		
	}

	bool empty(int stackNum) {
		return _ptops[stackNum] == -1;
	}

	int top(int stackNum) {
		if (empty(stackNum)) {
			throw std::exception("stack is empty");
		}
		return _buff[_ptops[stackNum]].value;
	}

	void pop(int stackNum) {
		if (empty(stackNum)) {
			throw std::exception("stack is empty");
		}
		_ptops[stackNum] = _buff[_ptops[stackNum]].preIdx;

		if (_ptops[stackNum] < _cur) {
			_buff[_ptops[stackNum]].preIdx = -1;
			_cur = _ptops[stackNum];
		}
	}

	size_t size(int stackNum) {
		int idx = _ptops[stackNum];
		if (idx == -1) {
			return 0;
		}
		else {
			size_t sz(1);
			while (_buff[idx].preIdx != -1) {
				sz++;
				idx = _buff[idx].preIdx;
			}
			return sz;
		}
	}
private:
	std::vector<node> _buff;
	int _ptops[3]; // absolute index
	int _totalSize;
	int _cur;
};

// circular array + shift elements if needed
class stack {
public:
	stack(int s=-1, int c=-1, int t=-1) : start(s), ptop(s-1), size(0), capacity(c), totalSize(t) {}

	bool isWithinStack(int idx) {
		if ((idx >= start) && (idx <= start + capacity - 1))
			return true;
		if ((start + capacity > totalSize) && (idx < (start + capacity) % totalSize))
			return true;
		return false;
	}

	int start;
	int ptop;
	int size;
	int capacity;
	int totalSize;
};

class threeStacks3 {
public:
	threeStacks3(int t = 300) {
		totalSize = t;
		stacks[0] = stack(0, totalSize/3, totalSize);
		stacks[1] = stack(totalSize/3, totalSize/3, totalSize);
		stacks[2] = stack(2*totalSize/3, totalSize/3, totalSize);
		buff.resize(totalSize);
	}

	void push(int stackNum, int v) {
		stack& cur = stacks[stackNum];
		if (cur.size >= cur.capacity) {
			if (totalElements() >= totalSize)
				throw std::exception("buffer is full!");
			else { 
				expand((stackNum + 1) % 3); 
			}
		}
		cur.ptop = nextElement(cur.ptop);
		buff[cur.ptop] = v;
		cur.size++;		
	}

	void pop(int stackNum) {		
		stack& cur = stacks[stackNum];
		if (cur.size == 0) {
			throw std::exception("stack is empty");
		}
		buff[cur.ptop] = 0;
		cur.ptop = previousElement(cur.ptop);
		cur.size--;
	}

	int top(int stackNum) {
		stack& cur = stacks[stackNum];
		return buff[cur.ptop];
	}

	size_t size(int stackNum) {
		stack& cur = stacks[stackNum];
		return cur.size;
	}

	bool empty(int stackNum) {
		stack& cur = stacks[stackNum];
		return cur.size == 0;
	}

private:
	void shift(int stackNum) {
		assert(totalElements() < totalSize);
		stack& cur = stacks[stackNum];
		// note if all full, infinite recurse		
		// but guarded by assert
		if (cur.size >= cur.capacity) {			
			int next = (stackNum + 1) % 3;
			shift(next); // recurse
			cur.capacity++;
		}
		
		// shift from end
		for (int i = (cur.start + cur.capacity - 1) % totalSize; i < cur.start; i = previousElement(i)) {
			buff[i] = buff[previousElement(i)];
		}

		// set default value for saved element
		buff[cur.start] = 0;

		// adjust the shifted stack with reduced size
		cur.start = nextElement(cur.start);
		cur.ptop = nextElement(cur.start);
		cur.capacity--;
	}

	void expand(int stackNum) {
		shift((stackNum + 1)%3);
		// add size to this stack
		stacks[stackNum].capacity++;
	}

	int nextElement(int idx) {
		if (idx + 1 >= totalSize)
			return 0;
		else
			return idx + 1;
	}

	int previousElement(int idx) {
		if (idx == 0)
			return totalSize-1;
		else
			return idx - 1;
	}

	int totalElements() {
		return stacks[0].size + stacks[1].size + stacks[2].size;
	}

private:
	stack stacks[3];
	std::vector<int> buff;
	int totalSize;
};

int main() {
	//threeStacks s;
	// threeStacks1 s;
	// threeStacks2 s;
	threeStacks3 s;
	for (int i = 0; i < 3; i++)
		std::cout << s.empty(i) << std::endl;
	for (int i = 0; i < 10; i++)
		s.push(0, i);
	for (int i = 100; i < 110; i++)
		s.push(1, i);
	for (int i = 1000; i < 1010; i++)
		s.push(2, i);

	for (int i = 0; i < 3; i++)
		std::cout << s.top(i) << std::endl;

	for (int i = 0; i < 3; i++) {
		s.pop(i);
		std::cout << s.top(i) << std::endl;
	}
	for (int i = 0; i < 3; i++) {
		s.pop(i);
		std::cout << s.size(i) << std::endl;
	}

	return 0;
}