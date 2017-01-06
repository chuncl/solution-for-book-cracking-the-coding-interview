// given a BT, each node contains a value. print all paths that sum of the node key to a given value. path does no necessarily start or end from root or at leaf

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

class BT {
public:
	BT(const vector<int>& vec) {
		if (!vec.empty()) {
			nodes.resize(vec.size());
			Node* h = nullptr;
			size_t cnt = 0;
			create_minimal_tree(h, nullptr, cnt, vec, 0, vec.size() - 1);
			root = &nodes[0];
		}
	}

	Node* getRoot() {
		return root;
	}


private:
	void create_minimal_tree(Node*& root, Node* parent, size_t& cnt, const vector<int>& vec, int start, int end) {
		if (start > end)
			return;

		int mid = (start + end) >> 1;
		nodes[cnt].key = vec[mid];
		nodes[cnt].parent = parent;
		root = &nodes[cnt++];

		create_minimal_tree(root->left, root, cnt, vec, start, mid - 1);
		create_minimal_tree(root->right, root, cnt, vec, mid + 1, end);
	}

private:
	vector<Node> nodes;
	Node* root;
};

/*
use parent pointer
IMPORTANT: starting from a node, and add back till root
DFS
*/

void printPath(Node* n, int level) {
	stack<int> s;
	for (int i = 0; i <= level; i++) {
		s.push(n->key);
		n = n->parent;
	}

	while (!s.empty()) {
		std::cout << s.top() << " ";
		s.pop();
	}

	std::cout << std::endl;
}

void findSum(Node* root, int sum) {
	if (root == nullptr)
		return;

	Node* n = root;
	int ans = 0;
	for (int i = 0; n; i++) {
		ans += n->key;
		if (ans == sum)
			printPath(root, i);
		n = n->parent;
	}

	// DFS
	findSum(root->left, sum);
	findSum(root->right, sum);
}

/*
Not use parent pointer.
Similar idea, starting from a node, and look up. but as no parent pointer, 
so we need additional buffer to record the path
DFS
*/
void printPath2(vector<int> path, int level) {
	for (size_t i = level; i < path.size(); i++) {
		cout << path[i] << " ";
	}
	cout << endl;
}

void findSum2_R(Node* root, int sum, vector<int> path) {
	if (root == nullptr)
		return;
	path.push_back(root->key);
	int tmp = 0;
	for (int i = path.size()-1; i >= 0; i--) {
		tmp += path.at(i);
		if (tmp == sum)
			printPath2(path, i);
	}
	// no need doing followings, as path is a copy, not reference
	//vector<int> v1(path);
	//vector<int> v2(path);
	findSum2_R(root->left, sum, path);
	findSum2_R(root->right, sum, path);
}

void findSum2(Node* root, int sum) {
	vector<int> path;
	findSum2_R(root, sum, path);
}

int main() {
	int a[] = {
		4, 3, 8, 5, 2, 1, 6
	};
	vector<int> arr(a, a + sizeof(a) / sizeof(int));
	BT t(arr);
	//findSum(t.getRoot(), 8);	
	findSum2(t.getRoot(), 8);

	return 0;
}