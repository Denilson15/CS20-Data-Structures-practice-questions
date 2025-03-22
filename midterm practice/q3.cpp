/*

You are allowed to discus the question but please write your own code.

Given a struct Node { int value; Node* left, * right; }; implement the functions below.

a)  int getSmallest(Node* r);  // return smallest value in the BST with root r. Assume r not null.


b)  Node* removeSmallest(Node* r); 
	
	remove smallest value in BST with root r. 
	Return pointer to the root of the modified tree.
	(Will normally be r unless smallest value was in the root.)  
	If r is null then just return nullptr.


Copy paste your code for just the functions.Don't use helper functions.

*/

struct Node {
	int value;
	Node* left;
	Node* right;
};

class BST{
public:
	Node* root;
	BST(Node* r) {
		root = r;
	}

	int getSmallest(Node* r) {
		if (r == nullptr) return -1;
		if (r->left == nullptr) return r->value;
		return getSmallest(r->left);
	}

	Node* removeSmallest(Node* r) {
		if (r == nullptr) return nullptr;


	}
};

