// write a function to check if a binary tree is banlanced. banlanced tree means the heights of 2 subtrees of any node never diff by more than one

#include <iostream>
#include <vector>
#include <algorithm>

/*Utility*/

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;	
};

struct BST {
	BST(const std::vector<int>& values) {
		nodes.resize(values.size());
		Node* h = nullptr;
		size_t cnt = 0;
		for (auto it = values.begin(); it != values.end(); it++) {
			insertR(h, *it, nullptr, cnt);
		}
	}
	Node* getRoot() {
		return nodes.empty() ? nullptr : &nodes[0];
	}
private:
	std::vector<Node> nodes;
	void insertR(Node*& head, int x, Node* parent, size_t& cnt) {
		// add node
		// head is changed, so it is Node*&
		if (head == nullptr) {				
			nodes[cnt].key = x;
			nodes[cnt].parent = parent;
			// cnt needs to be reference as it is the counter 
			// for the next nodes to be populated and needs to be updated
			head = &nodes[cnt++];
			return;
		}	

		// take current value of head as parent, no need to be rererence of pointer, as 
		// 1. no change on parent and
		// 2. even with change, it shall not be carried back
		parent = head;
		//BST
		if (x < head->key)
			// left is changed/created, as it is Node*&
			insertR(head->left, x, parent, cnt);
		else
			insertR(head->right, x, parent, cnt);
	}
};

/*SOLUTION*/

/* get heights of two sub-tree and check their difference
 if difference is no more than 1, recursely check banlance 
 on two sub-tress - as it is possible the 2 sub-trees height 
 difference is no more than 1, but 1 or both sub-trees is not banlanced itself.

 It is simple, but call getHeight on each node, so expensive O(N^2), repeatively called on a node
 */
int getHeight(Node* root) {
	if (root == nullptr)
		return 0;
	return std::max(getHeight(root->left), getHeight(root->right)) + 1;
}

bool isBanlanced(Node* root) {
	if (root == nullptr)
		return true;
	int heighDiff = std::abs(getHeight(root->left) - getHeight(root->right));
	if (heighDiff > 1)
		return false;
	else
		return isBanlanced(root->left) && isBanlanced(root->right);
}

/*
Check about banlance during the process getting height of a node. early return 
if a sub-tree is not banlanced ==> save a lot unnecessry checks.
O(N) time, O(H) space, H is tree height
*/
int getHeightWithCheck(Node* root)
{
	if (root == nullptr)
		return 0;
	int lh = getHeightWithCheck(root->left);
	if (lh == -1)
		return -1;
	int rh = getHeightWithCheck(root->right);
	if (rh == -1)
		return -1;
	int heightDiff = std::abs(lh - rh);
	if (heightDiff > 1)
		return -1;
	else
		return std::max(lh, rh) + 1;
}

bool isBanlanced2(Node* root) {
	if (getHeightWithCheck(root) == -1)
		return false;
	else
		return true;
}

/*
Implement a function to check if a tree is balanced. For the purposes of this question, 
a balanced tree is defined to be a tree such that no two leaf nodes differ in distance from the root by more than one.
NOTE: this is different in original statement!http://www.hawstein.com/posts/4.1.html
*/

// in-order to get all depths of leaf nodes
void getDepthOfLeaves(Node* root, int& depth, std::vector<int>& ret) {
	if (root == nullptr)
		return;
	depth++;
	getDepthOfLeaves(root->left, depth, ret);
	if ((root->left == nullptr) && (root->right == nullptr))
		ret.push_back(depth);
	getDepthOfLeaves(root->right, depth, ret);
	depth--;
}

// compare smallest and largest
bool isBanlanced3(Node* root) {
	std::vector<int> depths;
	int d = 0;
	getDepthOfLeaves(root, d, depths);
	if (depths.empty())
		return true;
	int min = *(std::min_element(depths.begin(), depths.end()));
	int max = *(std::max_element(depths.begin(), depths.end()));
	return (std::abs(max - min) <= 1);

}

int main() {
	/*int a[] = {
		5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11, 12
	}*/
		int a[] = {
		5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11
	};

	std::vector<int> values(a, a + sizeof(a) / sizeof(int));
	BST t(values);
	std::cout << isBanlanced(t.getRoot()) << std::endl;
	std::cout << isBanlanced2(t.getRoot()) << std::endl;	
	std::cout << isBanlanced3(t.getRoot()) << std::endl;

	int a2[] = {
		5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11, 12, 13
	};

	std::vector<int> values2(a2, a2 + sizeof(a2) / sizeof(int));
	BST t2(values2);

	std::cout << isBanlanced(t2.getRoot()) << std::endl;
	std::cout << isBanlanced2(t2.getRoot()) << std::endl;
	std::cout << isBanlanced3(t2.getRoot()) << std::endl;

	return 0;
}