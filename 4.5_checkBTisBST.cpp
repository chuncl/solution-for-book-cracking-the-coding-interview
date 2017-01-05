// check a BT is a BST

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

class BST {
public:
	BST(const std::vector<int>& vec) {
		if (!vec.empty()) {
			nodes.resize(vec.size());
			Node* r = nullptr;
			int cnt = 0;
			for (auto it = vec.begin(); it != vec.end(); it++) {
				insertR(r, *it, nullptr, cnt);
			}
			root = &nodes[0];
		}
	}

	Node* getRoot() {
		return root;
	}

private:
	void insertR(Node*&root, int x, Node* parent, int& cnt) {
		if (root == nullptr) {
			nodes[cnt].key = x;
			nodes[cnt].parent = parent;
			root = &nodes[cnt++];
			return;
		}

		parent = root;
		if (x <= root->key) 
			insertR(root->left, x, parent, cnt);
		else
			insertR(root->right, x, parent, cnt);	

	}
private:
	std::vector<Node> nodes;
	Node* root;
};

class BT {
public:
	BT(const std::vector<int>& vec) {
		if (!vec.empty()) {
			nodes.resize(vec.size());
			Node* r = nullptr;		
			int c = 0;
			create_minimal_BT_R(r, nullptr, c, vec, 0, vec.size()-1);		
			root = &nodes[0];
		}
	}

	Node* getRoot() {
		return root;
	}

private:
	void create_minimal_BT_R(Node*& root, Node* parent, int& cnt, const std::vector<int>& vec, int start, int end) {
		if (start > end)
			return;

		int mid = (start+end) >> 1;
		nodes[cnt].key = vec[mid];
		root = &nodes[cnt++];
		parent = root;

		create_minimal_BT_R(root->left, parent, cnt, vec, start, mid-1);
		create_minimal_BT_R(root->right, parent, cnt, vec, mid+1, start);
	}

private:
	std::vector<Node> nodes;
	Node* root;
};

// in-order traversal, copy BT nodes' key to arry
// if BST ==> sorted array
// NOTE: this only works if no duplicate
void copyBST_R(Node*root, std::vector<int>& vec) {
	if (root == nullptr) 
		return;
	copyBST_R(root->left, vec);
	vec.push_back(root->key);
	copyBST_R(root->right, vec);
}

bool checkBST(Node* root) {
	std::vector<int> arr;
	copyBST_R(root, arr);
	// we only need two value in the array to compare, 
	// why copy whole array?
	// ==> next improved solution
	for (size_t i = 1; i < arr.size(); i++) {
		if (arr[i] < arr[i-1])
			return false;
	}
	return true;
}

// still in-order taversal, 
// but just compare current node's value with previous one to save space O(n) ==> O(1)
// still require no duplicates
bool checkBST_R(Node* root, int& lastKey) {
	if (root == nullptr) 
		return true;
	
	if (!checkBST_R(root->left, lastKey))
		return false;
	
	if (root->key < lastKey) 
		return false;
	else
		lastKey = root->key;

	if (!checkBST_R(root->right, lastKey))
		return false;

	return true;
}

bool checkBST2(Node* root) {
	int lastVal = std::numeric_limits<int>::min();
	return checkBST_R(root, lastVal);
}

// min/max range 
// 1. check node's key within min/max range
// 2. branch left, update max
// 3. branch right, update min
// still require no duplicates
bool checkBST_R3(Node* root, int min, int max) {
	if (root == nullptr)
		return true;
	if ((root->key < min) || (root->key > max))
		return false;
	return checkBST_R3(root->left, min, root->key) &&
		checkBST_R3(root->right, root->key, max);
}

bool checkBST3(Node* root) {
	int min = std::numeric_limits<int>::min();
	int max = std::numeric_limits<int>::max();
	return checkBST_R3(root, min, max);
}

int main() {
	int a[] = { 5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11 };
	std::vector<int> arr(a, a+sizeof(a)/sizeof(int));
	BST t(arr);
	BT t2(arr);
	std::cout << checkBST(t.getRoot()) << std::endl;
	std::cout << checkBST(t2.getRoot()) << std::endl;

	 std::cout << checkBST2(t.getRoot()) << std::endl;
	 std::cout << checkBST2(t2.getRoot()) << std::endl;

	std::cout << checkBST3(t.getRoot()) << std::endl;
	std::cout << checkBST3(t2.getRoot()) << std::endl;
	return 0;
}