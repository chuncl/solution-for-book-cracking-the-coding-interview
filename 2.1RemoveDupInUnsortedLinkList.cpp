// Remove duplicates from an unsorted linked list. FOLLOW UP: what if no extra buffer is allowed?

#include <iostream>
#include <unordered_map>
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

// space O(n), time O(n)， not change order of LL
void removeDup(node* head)
{
	if ((head == nullptr) || (head->next == nullptr))
		return;

	// use buffer/hash
	std::unordered_map<int, bool> hash;	
	node* p = head, *q = head->next; // cannot say node* p = head, q = head->next;
	hash[head->data] = true;

	while (q) {
		if (hash[q->data]) {
			node* tmp = q;
			p->next = q->next;
			q = tmp->next;
			delete tmp;
		}
		else {
			hash[q->data] = true;
			p = p->next;
			q = q->next;			
		}
	}

	return;
}

void removeDupRHelper(node* head, std::unordered_map<int, bool>& hash)
{
	if ((head == nullptr) || (head->next == nullptr))
		return;

	node *q = head->next;

	if (hash[q->data] == true) {		
		head->next = q->next;
		delete q;
		removeDupRHelper(head, hash);
	}
	else {
		hash[q->data] = true;
		removeDupRHelper(q, hash);
	}
}


void removeDupR(node* head)
{
	if ((head == nullptr) || (head->next == nullptr))
		return;

	std::unordered_map<int, bool> hash;
	hash[head->data] = true;
	removeDupRHelper(head, hash);
}

// space O(1), time O(^2), not change order of LL
void removeDup2(node *head)
{
	if ((head == nullptr) || (head->next == nullptr))
		return;

	node* p, *q, *h = head;
	while (h->next) {
		p = h;
		q = h->next;
		while (q) {
			if (q->data == h->data) {
				node *tmp = q;
				p->next = q->next;
				q = p->next;
				delete tmp;
			}
			else {
				p = q;
				q = q->next;
			}
		}

		h = h->next;	
	}	
}

/* Merge sort based, space O(logn), time O(nlogn) */

// split in middle
void split(node* head, node** aHead, node**bHead)
{
	*aHead = head;

	// null or one node, no need to split
	if ((head == nullptr) || (head->next == nullptr)) {		
		*bHead = nullptr;
		return;
	}

	// slow fast pointer
	node* s = head, *f = head;
	while (f->next && f->next->next) {
		s = s->next;
		f = f->next->next;
	}

	*bHead = s->next;
	s->next = nullptr;	
}

// merge two sorted link-lists
node* merge(node* a, node* b)
{
	if (a == nullptr)
		return b;
	if (b == nullptr)
		return a;

	node*head;
	if (a->data <= b->data) {
		head = a;
		a = a->next;	
	}
	else {
		head = b;
		b = b->next;
	}

	node *p = head, *t;
	while (a && b) {
		t = (a->data <= b->data) ? a:b;		
		p->next = t;
		p = t;
		(a->data <= b->data) ? (a = a->next) : (b = b->next);
		p->next = nullptr;		
	}

	t = (a != nullptr) ? a : b;
	p->next = t;

	return head;
}

void mergesort(node** head)
{
	if ((*head == nullptr) || ((*head)->next == nullptr))
		return;

	// split
	node* aHead, *bHead;
	split(*head, &aHead, &bHead);

	// sort on each one
	mergesort(&aHead);
	mergesort(&bHead);
	// put it back
	*head = merge(aHead, bHead);
}

void removeDup3(node *head) {
	if ((head == nullptr) || (head->next == nullptr))
		return;

	// merge sort based
	mergesort(&head);

	node* p = head, *q = head->next;
	while (q) {
		// either find the 1st different node or null
		while (q && (q->data == p->data)) {
			q = q->next;
		}
		
		// delete nodes between p and q
		node *t = p->next;
		while (t != q) {
			node *n = t->next;
			delete t;
			t = n;
		}		

		// remove those node from LL
		p->next = q;
		p = q;
		if (q != nullptr) {
			q = q->next;
		}
	}
}

/* Utility funcitons*/
node* initLLHelper(const std::vector<int>& a, size_t idx);
node* initLL(const std::vector<int>& a) {
	return initLLHelper(a, 0);
}

node* initLLHelper(const std::vector<int>& a, size_t idx)
{
	assert(idx < a.size());
	size_t sz = a.size()-idx;
	if (sz == 0)
		return nullptr;
	if (sz == 1)
		return new node(a[idx], nullptr);

	node* next = initLLHelper(a, idx+1);
	node* head = new node(a[idx], next);
	return head;
	
}

void printLL(node* head)
{
	if (head == nullptr)
		return;
	if (head->next == nullptr)
		std::cout << head->data << std::endl;
	else {
		std::cout << head->data << "-->";
		printLL(head->next);
	}		
}

int main()
{
	std::vector<int> a = { 1, 2, 3, 4, 5 };
	std::vector<int> a1 = { 1, 2, 2, 3, 3, 4, 5 };
	std::vector<int> a2 = { 1, 4, 2, 3, 2, 4, 5 };
	std::vector<int> a3 = { 1, 4, 2, 3, 2, 4, 5, 1 };
	std::vector<int> a4 = { 1, 5, 2, 3, 2, 4, 5 };
	
	node* l  = initLL(a);
	node* l1 = initLL(a1);
	node* l2 = initLL(a2);
	node* l3 = initLL(a3);
	node* l4 = initLL(a4);	

	/*removeDup(l);
	printLL(l);
	removeDup(l1);
	printLL(l1);
	removeDup(l2);
	printLL(l2);
	removeDup(l3);
	printLL(l3);
	removeDup(l4);
	printLL(l4);*/

	/*removeDup2(l);
	printLL(l);
	removeDup2(l1);
	printLL(l1);
	removeDup2(l2);
	printLL(l2);
	removeDup2(l3);
	printLL(l3);
	removeDup2(l4);
	printLL(l4);*/

	/*removeDupR(l);
	printLL(l);
	removeDupR(l1);
	printLL(l1);
	removeDupR(l2);
	printLL(l2);
	removeDupR(l3);
	printLL(l3);
	removeDupR(l4);
	printLL(l4);*/

	removeDup3(l4);
	printLL(l4);
	
}

// cannot say node* p = head, q = head->next;

// for LL update pointer is p = p->next, not p++!

// check condition shall be p == nullptr, not p = nllptr!

