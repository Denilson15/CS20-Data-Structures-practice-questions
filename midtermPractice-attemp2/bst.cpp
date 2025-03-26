
#include <algorithm> //used for max function comparison
#include <queue>
using namespace std;

struct Node {
	int value;
	Node* right;
	Node* left;
};

bool isPerfect(Node* r) {
	if (r == nullptr) return true; //base case empty tree, this will also go off if none of the other return false lines ever execute
	if ((r->left != nullptr && r->right == nullptr) || (r->right != nullptr && r->left == nullptr)) return false; //case in which a right subtree exist but left doesnt or the vice versa left exists but right doesnt
	if (getHeight(r->left) != getHeight(r->right)) return false; //case in which the height is not equal then we return false
	return isPerfect(r->left) && isPerfect(r->right); //checks both the left and right subtrees to see what they return
}

int getHeight(Node* r) {
	if (r == nullptr) return -1; //checks if the treee is empty if it is the height will be negative 1 to indicate its empty
	int left = getHeight(r->left), right = getHeight(r->right); //here we are recursively going left and right and whatever is return from those calls will get assigned to left and right
	return max(left, right) + 1; //here that will compared, the values that are return are compared to see which is bigger and well add 1 so that we accurately calculate the height
}

bool isComplete(Node* r) {
	if (r == nullptr) return true; //base case empty tree
	queue<Node*> q; //initialize queue called q
	q.push(r); //push the root of our tree to the queue
	bool foundNull = false; //initialize a bool to false called foundNull which will track if we found a null value in our tree
	while (!q.empty()) { //loop that runs until our queue is empty, or as long as the queue is not empty
		Node* temp = q.front(); //New node created called temp, it will get assigned the value from the node at the front of the queue
		q.pop(); //we then can pop the root that we had pushed to the queue
		if (temp == nullptr) foundNull = true; //well then check if the temp variable is equal to a nullptr, if it it update foundnull to true
		else { //otherwise well be checking if found null is true, this is done to ensure that no other value pops up after, if it does after we've found a nullptr then that means its not a complete tree
			if (foundNull) return false; //so if temp is not equal to nullptr that means we found a value and if foundnull is set to true then that means we've found a value after finding the nullptr thus its false and not a complete tree
			q.push(temp->left), q.push(temp->right); //if that if statement above does not execute then were going to push the left and right subtrees to the queue
		}
	}
	return true; //if we have reached this point outside the loop we can return true since it means our tree is complete
}

bool isUnbalanced(Node* r) {
	if (r == nullptr) return false;
	int left = getHeight(r->left), right = getHeight(r->right); //recursively checking each tree and assigning whatever get height returns to left and right respectively
	if (left > right + 1 || right > left + 1) return true; //we then check if the difference between left and right is more than 1 then we return true since that means its unbalanced
	return isUnbalanced(r->left) || isUnbalanced(r->right); //here we are simply recursively checking each side if any side returns true than it is unbalanced hence the or
}

bool isStrictMinHeap(Node* r) {
	if (r == nullptr) return true; //case in which the tree is empty, true because an empty tree is a minheap
	if (!isComplete(r)) return false; //case in which the tree is not complete then we know is false because a minheap must be complete
	if ((r->left && r->left->value < r->value) || (r->right && r->right->value < r->value)) return false; //case in which r.left and r.right exist and one of them is less than the parent we return false
	return isStrictMinHeap(r->left) && isStrictMinHeap(r->right);  //here we just recursively check each left and right sub tree
}


int getSmallest(Node* r) {
	if (r == nullptr) return -1; //base case empty tree
	if (r->left == nullptr) return r->value; //traverse all the way left until we reach this base case, once this is true we return r.value since that would be the smallest node in the tree
	return getSmallest(r->left); //ensure we recursively return the value we found at the base case;
}


Node* removeSmallest(Node* r) {
	if (r == nullptr) return nullptr; //base case empty tree
	if (r->left == nullptr) { //found the smallest node
		Node* toDelete = r; //store that nodes address in a Node pointer called to delete, now toDelete has the address of that information
		r = r->right; //assign the address of the right subtree to the root, effectively updating the root
		delete toDelete; //delete the smallest node which was stored inside toDelete
		return r;//return this updated tree
	}
	r->left = removeSmallest(r->left); //whatever is recursively returned from the function will then be assigned to left subtree of the previous recursive call allowing the tree values to be updated
	return r;
}