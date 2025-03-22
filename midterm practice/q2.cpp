/*

Given a struct Node { int value; Node* left, * right; };, implement the functions below

// return true iff r is the root of a perfect binary tree.  (All levels full.)
a) bool isPerfect(Node* r); 

 // return the height of the tree with root r (empty tree has height 0).
b) int getHeight(Node* r);

// return true if r is the root of a complete binary tree.  
That means left and right subtrees have equal heights or left subtree has height greater by 1 than right subtree. 
In the former case, the left subtree must be perfect and the right subtree complete. 
In the latter case the left subtree must be complete and the right subtree perfect
c)bool isComplete(Node* r);  

// return true if tree is not empty and... 
left and right subtrees have heights that differ by more than one or  either left or right subtree is unbalanced.
d) bool isUnbalanced(Node* r);  

// Tree is a strict minheap:  Tree is complete and every node has a value strictly less than its children's values. 
(Empty tree qualifies.)
e) bool isStrictMinheap(Node* r); 

Copy paste your code for just the functions.


*/
#include <algorithm> 
using namespace std; 
struct Node {
	int value;
	Node* left;
	Node* right;
};

bool isPerfect(Node* r) {
	if (r == nullptr) return true;
	if (r->left == nullptr && r->right == nullptr) return true;
	if ((r->left != nullptr && r->right == nullptr) || (r->right != nullptr && r->left == nullptr)) return false;
	return isPerfect(r->left) && isPerfect(r->right);
}

int getHeight(Node* r) {
	if (r == nullptr) return -1;
	int left = getHeight(r->left);
	int right = getHeight(r->right);
	return max(left, right) + 1;
}

bool isComplete(Node* r) {

}

bool isUnbalanced(Node* r) {

}

bool isStrictMinheap(Node* r) {

}