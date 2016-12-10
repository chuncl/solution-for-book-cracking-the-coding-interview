//Implement an algorithm to delete a node in the middle of a singly linked list, given
// only access to that node.

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
bool delNode(node* c) 
{
	if ((c == nullptr) || (c->next == nullptr))
		return false;

	node* q = c->next;
	c->data = q->data;	
	c->next = q->next;
	delete q;
	return true;
}

/*TESTS*/
int main()
{
	int arr[] = { 1, 2, 3, 4, 5 };
	std::vector<int> a (arr, arr+sizeof(arr)/sizeof(int));
	node* l = initLL(a);
	printLL(l);
	bool ret = delNode(l->next);
	printLL(l);
	return 0;
}