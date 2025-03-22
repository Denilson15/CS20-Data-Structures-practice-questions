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
#include <algorithm> //used to call the max function to compare left and right inside of my getheight function, its not needed but it rather than using a conditional or the ternary operator
#include <queue> //used it to implement isComplete, following the level order approach we used in class
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
	if (r == nullptr) return true;
	q.push(r);
	bool isNull = false;
	while (!q.empty()) {
		Node* temp = q.front();
		q.pop();
		if (temp == nullptr) {
			isNull = true;
		}
		else {
			if (isNull) return false;
			q.push(temp->left);
			q.push(temp->right);
		}
	}
	return true;
}

bool isUnbalanced(Node* r) {
	if (r == nullptr) return false;
	int left = getHeight(r->left), 
		right = getHeight(r->right);
	if (left - right > 1 || right - left > 1) return true;
	return false;
}

bool isStrictMinheap(Node* r) {
	if (r == nullptr) return true;
	if (!isComplete(r)) return false;
	if ((r->left && r->left->value < r->value) || (r->right && r->right->value < r->value)) 
		return isStrictMinheap(r->left) && isStrictMinheap(r->right);
	return false;
}