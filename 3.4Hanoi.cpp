//In the classic problem of the Towers of Hanoi, you have 3 towers and N disks of different sizes which can slide onto any tower.The puzzle starts with disks sorted in ascending order of size from top to bottom(i.e., each disk sits on top of an even larger one).You have the following constraints :
//(T)Only one disk can be moved at a time.
//(2) A disk is slid off the top of one tower onto the next rod.
//(3) A disk can only be placed on top of a larger disk.
//Write a program to move the disks from the first tower to the last using Stacks.

#include <iostream>
#include <stack>
#include <cassert>

// recurse
void hanoi(int n, int orig, int des, int buff)
{
	if (n == 1) {
		std::cout << "move disk " << n << " from stack " << orig << " to " << des << std::endl;
		return;
	}

	hanoi(n - 1, orig, buff, des);
	std::cout << "move disk " << n << " from stack " << orig << " to " << des << std::endl;
	hanoi(n - 1, buff, des, orig);	
}

// use stack explictly, to  minminc recurse (system stack)
struct op {
	int start, end, orig, des, buff;
	op() {}
	op(int s, int e, int o, int d, int b) : start(s), end(e), orig(o), des(d), buff(b) {}
};


void hanoi2(int n, int orig, int des, int buff)
{
	std::stack<op> st;
	st.push(op(1, n, orig, des, buff));
	op curOp;
	while (!st.empty()) {
		curOp = st.top();
		st.pop();
		if (curOp.start != curOp.end) {
			st.push(op(curOp.start, curOp.end-1, buff, des, orig));
			st.push(op(curOp.end, curOp.end, orig, des, buff));
			st.push(op(curOp.start, curOp.end-1, orig, buff, des));
		}
		else {
			std::cout << "move disk " << n << " from stack " << orig << " to " << des << std::endl;
		}
	}
}

// use stack in tower to hold value, enssentially still recurse
class tower {
public:
	tower(int idx) : index(idx) {}

	void moveDisks(int n, tower& des, tower&buff) {
		if (n == 1) {
			std::cout << "move disk " << n << " from stack " << getidx() << " to " << des.getidx() << std::endl;
			return;
		}

		moveDisks(n - 1, buff, des);
		moveDisk(des);
		buff.moveDisks(n - 1, des, *this);	
	}

	void moveDisk(tower& des) {
		int n = top();
		des.push(n);
		pop();
		std::cout << "move disk " << n << " from stack " << getidx() << " to " << des.getidx() << std::endl;
	}

	int top() {
		return disks.top();
	}

	void push(int v) {
		assert(disks.empty() || (v <= top()));
		disks.push(v);
	}

	void pop() {
		disks.pop();
	}

	int getidx() {
		return index;
	}

private:
	std::stack<int> disks;
	int index;
};

void hanoi3(int n, int orig, int des, int buff) {
	tower towers[3] = {tower(0), tower(1), tower(2)};
	for (int i = n; i >= 1; i--) {
		towers[0].push(i);
	}
	
	towers[0].moveDisks(n, towers[2], towers[1]);
}

int main()
{
	 hanoi(3, 0, 2, 1);
	// hanoi2(3, 0, 2, 1);
	// hanoi3(3, 0, 2, 1);
	return 0;
}