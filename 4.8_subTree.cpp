//You have two very large binary trees: Tl, with millions of nodes, and T2, with
//hundreds of nodes. Create an algorithm to decide ifT2 is a subtree ofTl.
//A tree T2 is a subtree of Tl if there exists a node n in Tl such that the subtree ofn
//is identical to T2. That is, if you cut off the tree at node n, the two trees would be
//identical

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
	int key;
	Node* left;
	Node* right;
	Node* parent;
	// needed by hash solution (3)
	// NOTE the way to set a specific default value on one data memember
	int cached_hash = numeric_limits<int>::min();
	//Node() : key(0), left(nullptr), right(nullptr), parent(nullptr), cached_hash(numeric_limits<int>::min()) {}
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
		create_minimal_BST(root->right, root, cnt, vec, mid + 1, end);
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


/*
use pre-order + in-order approach:
1. if t2 is t1 sub-tree, then t2's string must be sub-string of t'1 string for both pre-order and in-order traversal
2. NOTE: need to use special character for null as other wise cannot differentiate (left 3)-(root 3) or (root 3) - (right 3)

Time complexity: O(n + m), as checking sub-string can be done in linear time (e.g., using sufix tree)
space comlexity: O(n + m)
*/
string to_string_compatible_NOTC11(int n)
{
	ostringstream ss;
	ss << n;
	return ss.str();
}

void pre_order(Node* root, string& ans) {
	if (root == nullptr) {
		ans.append("#");
		return;
	}

	ans.append(to_string_compatible_NOTC11(root->key));
	pre_order(root->left, ans);
	pre_order(root->right, ans);
}

void in_order(Node* root, string& ans) {
	if (root == nullptr) {
		ans.append("#");
		return;
	}

	in_order(root->left, ans);
	ans.append(to_string_compatible_NOTC11(root->key));
	in_order(root->right, ans);
}

bool isSubTree(Node* t1, Node* t2) {
	if (t2 == nullptr)
		return true;

	if (t1 == nullptr)
		return false;

	string pstr1, istr1, pstr2, istr2;
	pre_order(t1, pstr1);
	in_order(t1, istr1);
	pre_order(t2, pstr2);
	in_order(t2, istr2);

	return (pstr1.find(pstr2) != string::npos) &&
		(istr1.find(istr2) != string::npos);
}

/*
for each node in big tree t1, 
1. if its key match small tree's root, check if two tree match
2. other wise recuse on left & right child

Time complexity: O(n + km), where k is number of nodes in t1 that matches t2's root. it is not O(nm) as we dn't call treeMatch on all nodes of t1
Space: O(logn + log m)
*/
bool treeMatch(Node* r1, Node* r2) {
	if (r1 == nullptr)
		return r2 == nullptr;
	if (r2 == nullptr)
		return r1 == nullptr;

	if (r1->key != r2->key)
		return false;

	return treeMatch(r1->left, r2->left) &&
		treeMatch(r1->right, r2->right);
}

bool isSubTree2(Node* t1, Node* t2) {
	if (t2 == nullptr)
		return true;
	if (t1 == nullptr)
		return false;

	if (t1->key == t2->key)
		if (treeMatch(t1, t2))
			return true;

	return isSubTree2(t1->left, t2) ||
		isSubTree2(t1->right, t2);
}

/*
1. use hash, C11 hash hash<type> support, as functor
2. call functor hashFn on tree recursively node each node of the tree (staring from root)
3. compare tree match, just use hash value of root to compare is enough

Time complexity O(m+n)
speace complexity O(m+n) 
==> adding cached_hash in tree nodes + change data structure

but an interesting idea

*/

class hashFn {
public:
	int operator() (Node *n) {
		if (n == nullptr)
			return 0;
		if (n->cached_hash != numeric_limits<int>::min())
			return n->cached_hash;
		else {
			// call hash fucntion recursively on all tree nodes

			// hash<int> intHash;
			//int hash = 3 * intHash(n->key) + 5 * hashFn()(n->left->cached_hash) + 7 * hashFn()(n->right->cached_hash);
			int hashv = 3 * hash<int>()(n->key) + 5 * hashFn()(n->left) + 7 * hashFn()(n->right);
			n->cached_hash = hashv;
			return hashv;
		}
	}
};

bool treeMatch_hash(Node* r1, Node* r2) {
	return r1->cached_hash == r2->cached_hash;
}

bool isSubTree3_R(Node* t1, Node* t2) {
	if (t2 == nullptr)
		return true;
	if (t1 == nullptr)
		return false;
	if (treeMatch_hash(t1, t2))
		return true;

	return isSubTree3_R(t1->left, t2) ||
		isSubTree3_R(t1->right, t2);
}

bool isSubTree3(Node* t1, Node* t2) {
	/*hashFn hfnc;
	hfnc(t1);
	hfnc(t2);*/
	
	// OR different way to call functor, hashFn() create a tempory object and then call () operator on it
	hashFn()(t1);
	hashFn()(t2);

	return isSubTree3_R(t1, t2);
}

int main() {
	int a1[] = {
		0, 1, 2, 3, 4, 5, 6
	};
	vector<int> a1v(a1, a1 + sizeof(a1) / sizeof(int));
	int a2[] = {
		0, 1, 2
		//0, 1, 7
		//0, 1, 6
	};
	vector<int> a2v(a2, a2 + sizeof(a2) / sizeof(int));
	BST t1(a1v);
	BST t2(a2v);

	std::cout << isSubTree(t1.getRoot(), t2.getRoot()) << std::endl;
	std::cout << isSubTree2(t1.getRoot(), t2.getRoot()) << std::endl;
	std::cout << isSubTree3(t1.getRoot(), t2.getRoot()) << std::endl;


	return 0;
}