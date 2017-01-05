// find the first common ancester of 2 nodes in BT (not BST). Avoid storing additional nodes in data structure

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
};

class BST {
public:
	BST(const vector<int>& vec) {
		if (!vec.empty()) {
			nodes.resize(vec.size());
			Node* h = nullptr;
			size_t cnt = 0;
			create_minimal_BST(h, nullptr, cnt, vec, 0, vec.size() - 1);
			root = &nodes[0];
		}
	}

	Node* getRoot() {
		return root;
	}

	Node* search(int x) {
		return search_R(getRoot(), x);

	}

private:
	void create_minimal_BST(Node*& root, Node* parent, size_t& cnt, const vector<int>& vec, int start, int end) {
		if (start > end)
			return;

		int mid = (start + end) >> 1;
		nodes[cnt].key = vec[mid];
		nodes[cnt].parent = parent;
		root = &nodes[cnt++];

		create_minimal_BST(root->left, root, cnt, vec, start, mid - 1);
		create_minimal_BST(root->right, root, cnt, vec, mid+1, end);
	}

	Node* search_R(Node*root, int x) {
		if (x == root->key)
			return root;
		else if (x < root->key)
			return search_R(root->left, x);
		else
			return search_R(root->right, x);
	}

private:
	vector<Node> nodes;
	Node* root;
};

// use parent pointer & hash
// 1. hash all parents of one node, 
// 2. then check parents of q one by one in hash, starting from q.
Node* commonAncestor(Node* root, Node* p, Node* q) {
	if (!root || !p || !q)
		return nullptr;

	// hash all parents of one node
	map<Node*, bool> hash;
	while (p) {
		hash[p] = true;
		p = p->parent;
	}

	// check parents of q one by one in hash, starting from q
	while (q) {
		if (hash[q])
			return q;
		q = q->parent;
	}

	// take care the possibility that p or/and q is not in the tree
	return nullptr;
}

// utility, p cover q ==> p is ancstor of q
bool cover(Node* p, Node* q) {
	if (!p || !q)
		return false;

	if (p == q)
		return true;

	return cover(p->left, q) ||
		cover(p->right, q);
}

/* use parent pointer, but no hash
 1. get parent of one node one by one
 2. check if the parent node is ancestor of the other node
  ==> if yes, return
*/

Node* commonAncestor2(Node* root, Node* p, Node* q) {
	if (!root || !p || !q)
		return nullptr;
	while (p) {
		// check if the parent node is ancestor of the other node
		if (cover(p, q))
			return p;
		p = p->parent;
	}

	return nullptr;

}

/*
not use parent pointer
1. tree root is a common ancestor
2. start from tree node, going down, until find the first common ancestor
*/
void commonAncestor3(Node* root, Node* p, Node* q, Node*& ancestor) {
	if (!root || !p || !q)
		return;
	// "ancestor" is pointer reference, being updated when 
	// going down & if node is one of the common ancestors
	if (root && cover(root, p) && cover(root, q)) {
		ancestor = root;
		commonAncestor3(root->left, p, q, ancestor);
		commonAncestor3(root->right, p, q, ancestor);		
	}	
}

/*
not use parent poniter
1. p and q are in different side, return this node
2. otherwise, they are in the same side, go to that side to check recursively

time complexity: O(n) on a balanced tree.
because covers is called on 2n nodes in the first call
(n nodes for the left side, and n nodes for the right side). After that, the algorithm branches left or right, at which point covers will
be called on 2n/2 nodes, then 2n/4, and so on.This results in a runtime of 0(n)

*/
void commonAncestor4_R(Node* root, Node* p, Node* q, Node*& ans) {
	if (!root || !p || !q)
		return;
	bool is_p_on_left = cover(root->left, p);
	bool is_q_on_left = cover(root->left, q);

	if (is_p_on_left != is_q_on_left) {
		ans = root;
		return;
	}

	Node* child_side = is_p_on_left ? root->left : root->right;
	commonAncestor4_R(child_side, p, q, ans);
}

Node* commonAncestor4(Node* root, Node* p, Node* q) {
	if (!root || !p || !q)
		return nullptr;
	if (!(cover(root, p) && cover(root, q)))
		return nullptr;
	Node* result = nullptr;
	commonAncestor4_R(root, p, q, result);
	return result;
}

/*
MORE OPTIMAL: 
while previous solution is optimal in run time, it is inefficient in the way that, 
it calls cover from root, search all nodes under root, and then go to either left or right sub-tree to call it again
and so on ==> improvement, "bubble up" the findings to earlier nodes in the stack
1. return p if root's sub-tree contains only p (but not q)
2. return q if root's sub-tree contains only q (but not p)
3. return null if root's sub-tree contains neither q nor p
4. else return common ancestor of p & q

DFS
*/

void commonAncestor5_R(Node* root, Node* p, Node* q, Node*& ans) {
	if (!root || !p || !q)
		return;

	if ((root == p) || (root == q)) {
		ans = root;
		return;
	}

	Node* x = nullptr;
	commonAncestor5_R(root->left, p, q, x);
	// find first common acestor, return/pass through
	if (x && (x != p) && (x != q)) {
		ans = x;
		return;
	}

	Node* y = nullptr;
	commonAncestor5_R(root->right, p, q, y);
	// find first common acestor, return/pass through
	if (y && (y != p) && (y != q)) {
		ans = y;
		return;
	}

	if (x && y) { 
		// first common ancestor
		ans = root;
		return;
	}
	else {
		// bubble back p or q 
		// or null if nothing found
		ans = x ? x : y;
		return;
	}

}

Node* commonAncestor5(Node* root, Node* p, Node* q) {
	if (!root || !p || !q)
		return nullptr;
	
	// guard condition
	if (!(cover(root, p) && cover(root, q)))
		return nullptr;

	// degenerated case
	if (p == q) {		
		return p;
	}

	Node* ans = nullptr;
	commonAncestor5_R(root, p, q, ans);
	return ans;
}

int main() {
	std::vector<int> arr = { 0, 1, 2, 3, 4, 5, 6 };
	BST t(arr);
	Node* n1 = t.search(0);
	Node* n2 = t.search(4);
	Node* root = t.getRoot();
	
	Node* ans = commonAncestor(root, n1, n2);
	std::cout << "first common ancestor of Nodes: " << n1->key << " and " << n2->key << " is: " << ans->key << std::endl;	
	
	Node* ans2 = commonAncestor2(root, n1, n2);
	std::cout << "first common ancestor of Nodes: " << n1->key << " and " << n2->key << " is: " << ans2->key << std::endl;
	
	Node* ans3 = nullptr;
	commonAncestor3(root, n1, n2, ans3);
	std::cout << "first common ancestor of Nodes: " << n1->key << " and " << n2->key << " is: " << ans3->key << std::endl;

	Node* ans4 = commonAncestor4(root, n1, n2);
	std::cout << "first common ancestor of Nodes: " << n1->key << " and " << n2->key << " is: " << ans4->key << std::endl;

	Node* ans5 = commonAncestor5(root, n1, n2);
	std::cout << "first common ancestor of Nodes: " << n1->key << " and " << n2->key << " is: " << ans5->key << std::endl;

	return 0;
}