// Given a Binary tree, design an algorithm to create a LL for all the nodes at each depth (i.e., you have a BT of D depths, you get D LLs)

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

class BST {
public:
	BST(const std::vector<int>& vec) {
		nodes.resize(vec.size());
		Node *h = nullptr;
		size_t c = 0;
		for (auto it = vec.begin(); it != vec.end(); it++) {
			insertR(h, *it, nullptr, c);
		}
	}

	Node* getRoot() {
		return nodes.empty() ? nullptr : &nodes[0];
	}
private:	
	void insertR(Node*& root, int x, Node* parent, size_t& cnt) {
		if (root == nullptr) {
			nodes[cnt].key = x;
			nodes[cnt].parent = parent;
			root = &nodes[cnt++];
			return;
		}		
		if (x < root->key) {
			insertR(root->left, x, root, cnt);
		}
		else {
			insertR(root->right, x, root, cnt);
		}
	}
private:
	std::vector<Node> nodes;
};

typedef std::vector<std::list<Node*>> VEC_OF_LL;

void print(const VEC_OF_LL& lists) {
	for (auto it = lists.begin(); it != lists.end(); it++) {
		for (auto it2 = it->begin(); it2 != it->end(); it2++) {
			std::cout << (*it2)->key << " ";
		}
		std::cout << std::endl;
	}
}

/* first order traversal
 depth first traversal (DFS)
 */
void create_level_LLs_R(Node* root, VEC_OF_LL& lists, int level) {
	// base case
	if (root == nullptr)
		return;

	// first order traversal
	// IMPORTANT: when first time get to this level i, we must have seen level
	// 0 - level i-1, so 
	// 1. we use this to detect such case
	// 2. it is safe to add the new LL to end of result vector	
	if (lists.size() == level) {		
		std::list<Node*> ll;
		ll.push_back(root);
		lists.push_back(ll);
	}	
	else {
		lists[level].push_back(root);
	}

	// first order traversal
	create_level_LLs_R(root->left, lists, level + 1);
	create_level_LLs_R(root->right, lists, level + 1);
}

VEC_OF_LL create_level_LLs(Node* root) {
	VEC_OF_LL results;
	create_level_LLs_R(root, results, 0);
	return results;
}

/*
BFS
*/
VEC_OF_LL create_level_LLs_BFS(Node* root) {
	VEC_OF_LL lists;
	int level = 0;
	if (root != nullptr) {
		std::list<Node*> l;
		l.push_back(root);
		lists.push_back(l);
		while (!lists[level].empty()) {		
			std::list<Node*> t;
			for (auto it = lists[level].begin(); it != lists[level].end(); it++) {
				Node* n = *it;
				if (n->left != nullptr)
					t.push_back(n->left);
				if (n->right != nullptr)
					t.push_back(n->right);
			}
			level++;
			lists.push_back(t);
		}
	}

	return lists;
}

/*
BFS, 
slight variantion, not push to queue/vector first
*/
VEC_OF_LL create_level_LLs_BFS2(Node* root) {	
	VEC_OF_LL lists;
	if (root != nullptr) {
		std::list<Node*> cur;
		cur.push_back(root);
		while (!cur.empty()) {
			lists.push_back(cur);
			std::list<Node*> t;
			for (auto it = cur.begin(); it != cur.end(); it++) {
				Node* n = *it;
				if (n->left != nullptr)
					t.push_back(n->left);
				if (n->right != nullptr)
					t.push_back(n->right);
			}
			cur = t;
		}
	}
		
	return lists;
}



int main() {
	//std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> arr = { 5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11 };

	BST t(arr);
	//VEC_OF_LL r = create_level_LLs(t.getRoot());
	// VEC_OF_LL r = create_level_LLs_BFS(t.getRoot());
	VEC_OF_LL r = create_level_LLs_BFS2(t.getRoot());
	print(r);
	return 0;
}