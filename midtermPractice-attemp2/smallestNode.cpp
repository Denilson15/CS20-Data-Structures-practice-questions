
struct Node {
	int value;
	Node* left;
	Node* right;
};

int getSmalest(Node* r) {
	if (r == nullptr) return -1;
	if (r->left == nullptr) return r->value;
	return getSmalest(r->left);
}

Node* removeSmallest(Node* r) {
	if (r == nullptr) return nullptr; // base case empty tree
	if (r->left == nullptr) { // base case in which weve reached the smallest value
		Node* toDelete = r; //we then assign that smallest nodes memory to a toDelete node
		r = r->right; //we can now update that node to store the value of its right subtree which will either be null or the next smallest value in the tree
		delete toDelete; //now we can delete toDelete the node that was the smallest
		return r; // and we return r, the now updated root
	}
	r->left = removeSmallest(r->left); //this is the recursive call that goes left, it takes care of updating the tree by ensuring that we assign the tree returned to r.left
	return r; //in the cases where nothing is actually being updated we just return r to make sure the updated r inside the if statement makes its way back out
}


int getSmallest(Node* r) {
	if (r == nullptr) return -1; //base case empty tree
	if (r->left == nullptr) return r->value; //traverse all the way left until we reach this base case, once this is true we return r.value since that would be the smallest node in the tree
	return getSmalest(r->left); //ensure we recursively return the value we found at the base case;
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