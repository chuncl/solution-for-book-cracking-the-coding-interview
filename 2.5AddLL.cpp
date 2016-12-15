// two LLs representing two numbers. each node represents one digit. represent in reverse order, such as 1st digit is the head of LL, write a function to add two numbers and return such as LL
// FOLLOW UP: what if the number is represented in forward order

#include <iostream>
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

/* SOLUTION 1*/
node* addLLHelper(node* l1, node* l2, int carry) 
{
	if ((l1 == nullptr) && (l2 == nullptr) && (carry == 0)) {
		return nullptr;
	}

	int value(carry);
	if (l1 != nullptr) {
		value += l1->data;
	}
	if (l2 != nullptr) {
		value += l2->data;
	}

	node *ret = new node(value % 10, nullptr);

	ret->next = addLLHelper(((l1 == nullptr) ? nullptr : l1->next),
		((l2 == nullptr) ? nullptr : l2->next), (value / 10));

	return ret;
}
node* addLL(node* l1, node* l2)
{
	return addLLHelper(l1, l2, 0);
}

/* SOLUTION 1.2 - interation*/

node* addLLIter(node* l1, node* l2)
{
	if (l1 == nullptr)
		return l2;
	if (l2 == nullptr)
		return l1;

	node* ret, *p = nullptr;
	int carry = 0;
	while (l1 && l2) {
		int t = l1->data + l2->data + carry;
		node* n = new node(t%10, nullptr);
		carry = t / 10;
		if (p) {
			p->next = n;
			p = n;
		}
		else {
			ret = p = n;
		}

		l1 = l1->next;
		l2 = l2->next;
	}

	while (l1) {
		int t = l1->data + carry;
		node* n = new node(t % 10, nullptr);
		carry = t/10;
		p->next = n;
		p = n;
		l1 = l1->next;
	}

	while (l2) {
		int t = l2->data + carry;
		node* n = new node(t % 10, nullptr);
		carry = t / 10;
		p->next = n;
		p = n;
		l2 = l2->next;
	}

	if (carry) {
		node* n = new node(carry, nullptr);
		p->next = n;
	}

	return ret;
	
}

/* SOLUTION 2 - FOLLOW UP*/
node* addLLhelperR2(node* l1, node* l2, int& carry)
{
	// assume same length & last node is the 1st digit
	if (l1 == nullptr) {
		assert((l2 == nullptr) && (carry == 0));		
		return nullptr;
	}

	node* next = addLLhelperR2(l1->next, l2->next, carry);

	int value = carry + l1->data + l2->data;
	node *ret = new node(value % 10, next);
	carry = value / 10;
	return ret;

}

node* addLLhelper2(node* l1, node* l2) {
	int carry(0);
	node* n = addLLhelperR2(l1, l2, carry);
	return carry ? new node(carry, n) : n;
}

node* paddLLFront(node* h, int n)
{	
	if (n > 0) {
		// pad front
		node* ret = new node(0, h);
		// recurse
		return paddLLFront(ret, n - 1);
	}
	else {
		// base condition
		return h;
	}
}

void paddLLs(node** h1, node** h2)
{
	node* l1 = *h1, *l2 = *h2;
	int sz1 = 0, sz2 = 0;	
	while (l1) {
		sz1++;
		l1 = l1->next;
	}

	while (l2) {
		sz2++;
		l2 = l2->next;
	}	
	// pad front in the shorter LL
	if (sz1 > sz2) {
		*h2 = paddLLFront(*h2, sz1 - sz2);
	}
	else {
		*h1 = paddLLFront(*h1, sz2 - sz1);
	}
}


node* addLL2(node* l1, node* l2)
{
	node* h1(l1), *h2(l2);
	paddLLs(&h1, &h2);
	int carry = 0;
	return addLLhelper2(h1, h2);

}

int main()
{
	std::vector<int> a = { 7, 1, 6};
	std::vector<int> a1 = { 5, 9, 2};
	std::vector<int> a2 = { 1, 4 };
	std::vector<int> a3 = { 2, 6, 3};	
	std::vector<int> a4 = { 7, 1, 6 };
	std::vector<int> a5 = { 5, 9, 3 };

	node* l = initLL(a);
	node* l1 = initLL(a1);
	node* l2 = initLL(a2);
	node* l3 = initLL(a3);
	node* l4 = initLL(a4);
	node* l5 = initLL(a5);

	//node* ret1 = addLL(l, l1);
	//printLL(ret1);
	//node* ret2 = addLL(l2, l3);
	//printLL(ret2);
	//node* ret3 = addLL(l4, l5);
	//printLL(ret3);

	node* ret1_it = addLLIter(l, l1);
	printLL(ret1_it);
	node* ret2_it = addLLIter(l2, l3);
	printLL(ret2_it);
	node* ret3_it = addLLIter(l4, l5);
	printLL(ret3_it);

	//node* ret1_2 = addLL2(l, l1);
	//printLL(ret1_2);
	//node* ret2_2 = addLL2(l2, l3);
	//printLL(ret2_2);
	//node* ret3_2 = addLL2(l4, l5);
	//printLL(ret3_2);



	return 0;
}