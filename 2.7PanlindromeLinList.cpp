// check if a LL is a panlindrom


#include <iostream>
#include <vector>
#include <stack>
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

/*SOLUTION1*/
node* revertLLR(node* h, node*& tail)
{
	if (h == nullptr)
		return nullptr;
	if (h->next == nullptr) {
		tail = new node(h->data, nullptr);
		return tail;
	}

	node* head = revertLLR(h->next, tail);
	node* cur = new node(h->data, nullptr);
	tail->next = cur;
	tail = cur;
	return head;
}

node* revertLL(node* h)
{
	node* tail = nullptr;
	return revertLLR(h, tail);
}

bool isPanlindrome(node* l)
{

	node* l2 = revertLL(l);
	node* d = l2;

	while(l2 && l) {
		if (l2->data != l->data) {
			return false;
		}
		l2 = l2->next;
		l = l->next;
	}

	assert((l2 == nullptr) && (l == nullptr));

	while(d) {
		node* t = d;
		d = d->next;
		delete t;		
	}

	return true;
}

/*SOLUTION2*/

bool isPanlindrome2(node* h)
{
	if ((h== nullptr) || (h->next == nullptr))
		return true;

	std::stack<node*> stack;
	node* slow = h;
	node* fast = h;		
	while(fast && fast->next) {				
		stack.push(slow);
		slow = slow->next;				
		fast = fast->next->next;		
	}

	// odd number of nodes, so skip middle node
	if (fast) {
		slow = slow->next;	
	}

	while (slow) {
		node* cur = stack.top();
		if (cur->data != slow->data)
			return false;
		stack.pop();
		slow = slow->next;
	}

	return true;
}

/*SOLUTION3*/
bool isPanlindromeR(node* h, int len, node*& tail)
{
	if ((h == nullptr) || len == 0) {
		tail = nullptr;
		return true;
	}

	if (len == 1) {
		tail = h->next;
		return true;
	}
	if (len == 2) {
		tail = h->next->next;
		return (h->data == h->next->data);
	}

	node* t = nullptr;
	bool ret = isPanlindromeR(h->next, len-2, t);
	tail = t->next;
	return ret && (h->data == t->data);

}

bool isPanlindrome3(node* h)
{
	int count = 0;
	for (node* p = h; p; p = p->next) {
		count++;
	}
	node* t = nullptr;
	return isPanlindromeR(h, count, t);	
}


int main()
{
	int arr[] = { 2, 6, 1, 6, 2};
	std::vector<int> a(arr, arr+sizeof(arr)/sizeof(int));

	int arr1[] = { 2, 6, 6, 2};
	std::vector<int> a1(arr1, arr1+sizeof(arr1)/sizeof(int));

	int arr2[] = { 2, 6, 1, 7, 2};
	std::vector<int> a2(arr2, arr2+sizeof(arr2)/sizeof(int));

	node* l = initLL(a);
	node* l1 = initLL(a1);
	node* l2 = initLL(a2);
	
	std::cout << isPanlindrome(l) << std::endl;
	std::cout << isPanlindrome(l1) << std::endl;
	std::cout << isPanlindrome(l2) << std::endl;


	std::cout << isPanlindrome2(l) << std::endl;
	std::cout << isPanlindrome2(l1) << std::endl;
	std::cout << isPanlindrome2(l2) << std::endl;

	std::cout << isPanlindrome3(l) << std::endl;
	std::cout << isPanlindrome3(l1) << std::endl;
	std::cout << isPanlindrome3(l2) << std::endl;

	return 0;
}
