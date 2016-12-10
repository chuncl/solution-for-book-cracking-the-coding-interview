// partition a LL around value x, such that all nodes less than X comes before nodes equal or large than x.

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

/* SOLUTION*/

// 2 LL, insert node behind (4 pointers, 2 end pointers for insert, 2 start pointers for put together and return)
void partition(node** head, int x)
{
	if (head == nullptr || (*head == nullptr) || ((*head)->next ==nullptr))
		return;

	node* aStart(nullptr), *aEnd(nullptr), *bStart(nullptr), *bEnd(nullptr), *p = *head;	
	while(p) {
		if (p->data < x) {
			if (aStart == nullptr) {
				aStart = p;
				aEnd = aStart;
			} else {
				aEnd->next = p;
				aEnd = aEnd->next;
			}
			p = p->next;
			aEnd->next = nullptr;
		} else {
			if (bStart == nullptr) {
				bStart = p;
				bEnd = bStart;
			} else {
				bEnd->next = p;
				bEnd = bEnd->next;
			}
			p = p->next;
			bEnd->next = nullptr;
		}		
	}

	if (aStart == nullptr) {
		*head = bStart;
		return;
	}

	if (bStart == nullptr) {
		*head = aStart;
		return;
	}

	aEnd->next = bStart;
	*head = aStart;
	return;	
}

// 2 LL, insert node beforhand (2 start pointers)
void partition2(node** head, int x)
{

	if (head == nullptr || (*head == nullptr) || ((*head)->next ==nullptr))
		return;
	node* aStart(nullptr), *bStart(nullptr), *p = *head;	
	while(p) {
		node* n = p->next;
		if (p->data < x) {
			p->next = aStart;
			aStart = p;		
		} else {
			p->next = bStart;
			bStart = p;			
		}
		p = n;
	}

	if (aStart == nullptr) {
		*head = bStart;
		return;
	}

	// find first LL's last node and link to 2nd LL
    p = aStart;
	for (p = aStart; p->next; p = p->next) {}
	p->next = bStart;
	*head = aStart;
	return;	
}

/*TESTS*/
int main()
{
	int arr[] = { 1, 4, 10, 20, 6 , 2, 3};
	std::vector<int> a (arr, arr+sizeof(arr)/sizeof(int));
	node* l = initLL(a);
	partition(&l, 6);
	printLL(l);
	partition2(&l, 6);
	printLL(l);
	return 0;
}

// considering adding to either LL's head or end