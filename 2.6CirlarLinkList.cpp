// given a circlar LL, write a function to return the node at begning of the loop

#include <iostream>
#include <vector>
#include <cassert>
#include <set>

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
node* initLLHelper(const std::vector<int>& a, size_t idx, size_t n, node*& tail);
node* initLL(const std::vector<int>& a, size_t n) {
	node* t = nullptr;
	return initLLHelper(a, 0, n, t);
}

node* initLLHelper(const std::vector<int>& a, size_t idx, size_t n, node*& tail)
{
	assert(idx < a.size());
	size_t sz = a.size() - idx;
	if (sz == 0)
		return nullptr;
	if (sz == 1) {
		tail = new node(a[idx], nullptr);
		return tail;
	}

	node* next = initLLHelper(a, idx + 1, n, tail);
	node* head = new node(a[idx], next);

	if (idx == n) {
		tail->next = head;
	}

	return head;

}

//void printLL(node* head)
//{
//	if (head == nullptr) {
//		std::cout << "NULL";
//		return;
//	}
//	if (head->next == nullptr)
//		std::cout << head->data << std::endl;
//	else {
//		std::cout << head->data << "-->";
//		printLL(head->next);
//	}
//}

/* SOLUTION 1*/

node* findBegining(node* head)
{
	if (head == nullptr) 
		return nullptr;

	node* s = head;
	node* f = head;
	
	while ((f != nullptr) && (f->next != nullptr)) {
		s = s->next;
		f = f->next->next;
		if (s == f) 
			break;
	}

	if (s != f)
		return nullptr;

	s = head;
	while (s != f) {
		s = s->next;
		f = f->next;
	}

	return s;
}


/* SOLUTION 2*/
node* findBegining2(node* head)
{
	node*p = head;
	std::set<node*> s;	
	
	while(p) {
		std::pair<std::set<node*>::iterator, bool> ret = s.insert(p);
		if (!ret.second) {
			return *(ret.first);
		}
	}

	return nullptr;
}

int main()
{
	int arr[] = {
		3, 2, 1, 3, 5, 6, 2, 6, 3, 1 
	};

	std::vector<int> a(arr, arr+sizeof(arr)/sizeof(int));
	node* l = initLL(a, 5);

	node*p = findBegining(l);

	if (p)
		std::cout<<p->data<<std::endl;

	node*p2 = findBegining2(l);
	if (p2)
		std::cout<<p->data<<std::endl;


	return 0;
}