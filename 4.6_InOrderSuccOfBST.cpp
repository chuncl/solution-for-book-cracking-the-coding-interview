// find next node of a given node of BST (in-order successor). you can assume there is link to parent

#include <iostream>
#include <vector>

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

	Node* search (int x) {
		Node* r = getRoot();
		return search_R(r, x);	
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

	Node* search_R (Node* root, int x) {		
		if (!root) 
			return nullptr;
		if (root->key == x)
			return root;
		else if (x < root->key)
			return search_R(root->left, x);
		else
			return search_R(root->right, x);	
	}

private:
	std::vector<Node> nodes;
	Node* root;
};

// left-most child
Node* getMinimal(Node* root) {
	if (root == nullptr)
		return nullptr;

	while (root->left) {
		root = root->left;
	}

	return root;
}

Node* getInOrderSucc(Node* node) {
	if (node == nullptr)
		return nullptr;

    // if it has right sub-tree, find the minmal (left-most child)
	if (node->right)
		return getMinimal(node->right);

	// otherwise, go up, until find a node (parent)
	// whose left child is current node (with larger key )
//	We need to
//traverse upwards from q until we find a node x that we have nof fully traversed. How
//do we know that we have not fully traversed a node x? We know we have hit this case
//when we move from a left node to its parent. The left node is fully traversed, but its
//parent is not.

	Node* p = node->parent;
	while(p && (node == p->right)) {
		node = p;
		p = p->parent;
	}

	return p;
}

int main() {
	int a[] = { 5, 3, 8, 1, 4, 7, 10, 2, 6, 9, 11 };
	std::vector<int> arr(a, a+sizeof(a)/sizeof(int));
	BST t(arr);
	std::cout << "root is " << t.getRoot()->key << std::endl;
	std::cout << "successor is " << getInOrderSucc(t.getRoot())->key << std::endl;

	int a2[] = { 8, 2, 4, 6, 5, 10 };
	std::vector<int> arr2(a2, a2+sizeof(a2)/sizeof(int));
	BST t2(arr2);
	Node* n = t2.search(6);
	std::cout << "input is " << n->key << std::endl;
	std::cout << "successor is " << getInOrderSucc(n)->key << std::endl;

	return 0;
}