// given a sorted (increasing order) arrray with unique elements, write an algorithm to build a BST with minimal height

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

class BST {
public:
	BST(const std::vector<int>& sortedArr) {
		nodes.resize(sortedArr.size());
		Node* r = nullptr;
		size_t cnt = 0;
		create_minimal_BST_R(r, nullptr, cnt, sortedArr, 0, sortedArr.size()-1);
	}

	Node* getRoot() {
		return &nodes[0];
	}

	int getHeigh() {
		return getHeightR(getRoot());
	}	

private:
	std::vector<Node> nodes;
	void create_minimal_BST_R(Node*& root, Node* parent, size_t& cnt, const std::vector<int>& sortedArr, int start, int end) {
		// base condition
		if (start > end)
			return;
		// get middle element & create node
		int mid = (start + end) >> 1;
		nodes[cnt].key = sortedArr[mid];
		nodes[cnt].parent = parent;
		root = &nodes[cnt++];		
		// recurse
		create_minimal_BST_R(root->left, root, cnt, sortedArr, start, mid - 1);
		create_minimal_BST_R(root->right, root, cnt, sortedArr, mid+1, end);
	}

	int getHeightR(Node* root) {
		if (root == nullptr)
			return 0;
		return std::max(getHeightR(root->left), getHeightR(root->right)) + 1;
	}

};

int main() {	
	//std::vector<int> arr = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> arr = { 0, 1, 2};
	BST t(arr);
	std::cout << t.getHeigh() << std::endl;
}