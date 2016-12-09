// find kth to the last element in singly linked list
// last node counted as 0th to the last element

#include <iostream>
#include <stack>
#include <vector>
#include <cassert>

struct node
{
	int data;
	node* next;
	node(int d, node* n) {
		data = d;
		next = n;
	}
};

/* Utility funcitons*/
node* initLLHelper(const std::vector<int>& a, size_t idx);
node* initLL(const std::vector<int>& a) {
	return initLLHelper(a, 0);
}

node* initLLHelper(const std::vector<int>& a, size_t idx)
{
	assert(idx < a.size());
	size_t sz = a.size() - idx;
	if (sz == 0)
		return nullptr;
	if (sz == 1)
		return new node(a[idx], nullptr);

	node* next = initLLHelper(a, idx + 1);
	node* head = new node(a[idx], next);
	return head;

}

void printLL(node* head)
{
	if (head == nullptr) {
		std::cout << "NULL";
		return;
	}
	if (head->next == nullptr)
		std::cout << head->data << std::endl;
	else {
		std::cout << head->data << "-->";
		printLL(head->next);
	}
}

/*SOLUTION*/

// use stack explictly, time O(N) space O(N)
node* findKToLast(node* head, size_t k)
{
	if (head == nullptr)
		return nullptr;

	std::stack<node*> s;
	while (head->next) {
		s.push(head);
		head = head->next;
	}

	for (size_t idx = k; (idx > 1) && !s.empty(); idx--) {
		s.pop();		
	}

	if (s.empty())
		return nullptr;

	return s.top();

}


// Recursive, time O(N) space O(N)
node* findKToLast2(node* head, int& k) {
	if (head == nullptr)
		return nullptr;
	node* ret = findKToLast2(head->next, k);
	k--;
	if (k == -1) {
		ret = head;		
	}
	return ret;
}

// Iterative, fast slow pointer, time O(N), space O(1)
node* findKToLast3(node*head, size_t k)
{
	if (head == nullptr)
		return nullptr;
	node* s = head, *f = head;

	while(f && (k > 0)) {
		f = f->next;
		k--;
	}

	if (f == nullptr)
		return nullptr;

	while (f->next) {
		s = s->next;
		f = f->next;
	}

	return s;
}


/*TESTS*/
int main()
{
	std::vector<int> a = { 1, 2, 3, 4, 5 };
	node* l = initLL(a);	
	node* l1 = nullptr;

	node* r = findKToLast(l, 1);
	std::cout << r->data << std::endl;
	node* r1 = findKToLast(l, 3);
	std::cout << r1->data << std::endl;
	node* r2 = findKToLast(l, 6);
	assert(r2 == nullptr);
	
	int k = 1;
	node* r_2 = findKToLast2(l, k);
	std::cout << r_2->data << std::endl;
	k = 3;
	node* r1_2 = findKToLast2(l, k);
	std::cout << r1_2->data << std::endl;
	k = 6;
	node* r2_2 = findKToLast2(l, k);
	assert(r2_2 == nullptr);

	node* r_3 = findKToLast3(l, 1);
	std::cout << r_3->data << std::endl;
	node* r1_3 = findKToLast3(l, 3);
	std::cout << r1_3->data << std::endl;
	node* r2_3 = findKToLast3(l, 6);
	assert(r2_3 == nullptr);

	return 0;
}