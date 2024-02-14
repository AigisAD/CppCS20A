#include"bst.h"
#include<functional>
#include<iostream>
#include<assert.h>

// Node implementation: Implemented
struct BinarySearchTree::Node {
	Node(int v, Node *l, Node *r) :value(v), left(l), right(r) {}
	Node() :Node(0, nullptr, nullptr) {}

	int value;
	Node *left, *right;
};

//----------------------------------------------------------
//-------------- Binary Search Tree Function Implementations 
// 
//  Public Interface functions
// 		Completley Implemented, nothing to do.  These functions 
//      call the recursive helper functions you will implement.
// 
// Constructor
BinarySearchTree::BinarySearchTree() :m_root(nullptr) {}

// Destructor
BinarySearchTree::~BinarySearchTree() {

	//Use the post order traversal to delete the nodes.
	//lambda function to delete a node n: 
	//				[](Node* n) {delete n; } 
	postorder(m_root, [](Node* n) {delete n; });
}

void BinarySearchTree::printInorder(){

	//Use inorder traversal to print values in a node in the tree.
	//lambda function to print the value in a node:
	//				[](Node* n) {std::cout << n->value << std::endl; }
	inorder(m_root, [](Node* n) {std::cout << n->value << " "; });
	std::cout << std::endl;
}
void BinarySearchTree::printPreorder() {

	//Use pre order traversal to print values in a node in the tree.
	//lambda function to print the value in a node:
	//				[](Node* n) {std::cout << n->value << std::endl; }
	preorder(m_root, [](Node* n) {std::cout << n->value << " "; });
	std::cout << std::endl;
}
void BinarySearchTree::printPostorder(){

	//Use post order traversal to print values in a node in the tree.
	//lambda function to print the value in a node:
	//				[](Node* n) {std::cout << n->value << std::endl; }
	postorder(m_root, [](Node* n) {std::cout << n->value << " "; });
	std::cout << std::endl;
}
void BinarySearchTree::insert(int value) {
	m_root = insert(m_root, value);
}
void BinarySearchTree::remove(int value) {
	m_root = deleteNode(m_root, value);
}
int	BinarySearchTree::min() const {

	assert(m_root != nullptr);

	Node *node = minNode(m_root);
	return node->value;
}
int	BinarySearchTree::max() const {

	assert(m_root != nullptr);

	Node *node = maxNode(m_root);
	return node->value;
}
int	BinarySearchTree::height() const {

	return height(m_root);
}
bool BinarySearchTree::search(int value) const {
	Node *node = search(m_root, value);
	return (node != nullptr);
}

bool BinarySearchTree::isEmpty() const {
	return (m_root == nullptr);
}

void BinarySearchTree::printTree() const {

	printTree(m_root,0);
}

//----------------------------------------------------------
//
// Private Recursive Functions
//


// Inorder Traversal: Implemented so you can see how passing a function into 
// another function works, other traversals left for you to implement.  the second
// parameter, proc, is a function and we see that its return type is void and it 
// has a Node* as a parameter.  Any function of that form passed into _inorder will be
// called as seen below.  
void BinarySearchTree::inorder(Node* node, std::function<void(Node*)> proc) {
	if (node == nullptr) return;

	inorder(node->left, proc);
	proc(node);
	inorder(node->right, proc);

}

void BinarySearchTree::postorder(Node* node, std::function<void(Node*)> proc) {
	if (node == nullptr) return;

	postorder(node->left, proc);
	postorder(node->right, proc);
	proc(node);


}

void BinarySearchTree::preorder(Node* node, std::function<void(Node*)> proc) {
	if (node == nullptr) return;

	proc(node);
	preorder(node->left, proc);
	preorder(node->right, proc);
	
}
 
// BinarySearchTree::_insert recursively inserts into the BST according 
// to the rules of the BST.  
BinarySearchTree::Node* BinarySearchTree::insert(Node *node, int value) {
	if (node == nullptr) {
		node = new Node(value,nullptr,nullptr);
		return node;
	}
	if (search(value) == true)
		return node;
	if (value < node->value) {
		if (node->left == nullptr) {
			node->left = new Node(value, nullptr, nullptr);
			return node;
		}
		insert(node->left, value);
	}
	else {
		if (node->right == nullptr) {
			node->right = new Node(value, nullptr, nullptr);
			return node;
		}
		insert(node->right, value);
	}
	return node;

}

// BinarySearchTree::_search recursively searches the tree for value.
BinarySearchTree::Node* BinarySearchTree::search(Node *node, int value) const {
	if (node == nullptr)
		return nullptr;
	else if (value == node->value)
		return node;
	else if (value < node->value)
		search(node->left, value);
	else 
		search(node->right, value);

}

// BinarySearchTree::_height
// Height of a binary tree is the height of the largest subtree + 1
// An empty tree has height 0;
int	BinarySearchTree::height(Node* node) const {
	if (node == nullptr)
		return 0;
	else {
		int leftSide = height(node->left);
		int rightSide = height(node->right);
		if (leftSide > rightSide)
			return (1 + leftSide);
		else
			return (1 + rightSide);
	}
}
// BinarySearchTree::_min recursively obtain the node with the minimum value
BinarySearchTree::Node*	BinarySearchTree::minNode(Node *node) const  {
	if (node == nullptr||node->left==nullptr)
		return node;
	minNode(node->left);

}

// BinarySearchTree::_max recursively obtain the node with the minimum value
BinarySearchTree::Node*	BinarySearchTree::maxNode(Node *node) const {
	if (node == nullptr || node->right == nullptr)
		return node;
	maxNode(node->right);
	
}

// BinarySearchTree::_printTree
// Prints the BST in a tree format rotated -90 degrees.  Uses space to 
// signify the space between levels of the tree. Uses the inorder 
// traversal but traverses right first, rather than left. Cannot use
// any of the other travel functions because of this.
//
// parameter space determines the number of spaces needed for each level.
// Example binary shows 5 spaces between levels. 
//
// i.e. traverse right 
//		print appropriate number of spaces 
//		print value 
//		traverse left
void BinarySearchTree::printTree(Node *node, int space = 0) const {
	if (node == nullptr) 
		return;
	printTree(node->right, space+5);
	for (int i = 0; i < space; i++)
		std::cout << " ";
	std::cout << node->value << std::endl;
	
	printTree(node->left, space+5);
	





}


//BinarySearchTree::_deleteNode
//
// Make sure you're comfortable with the iterative solution seen in the lecture slides
// before thinking about how to do it recursively.
//
// Recursively removes a node in the binary tree.  The recursive algorithm will 
// be different than the iterative algorithm.  The iterative algorithm conisted
// of first finding the node using two pointers so that we know how to rearrange
// the children of the deleted node. In recursion we are passing in the sub trees
// each recursive step, so by definition we already have a handle on each subtrees'
// parents (it is the node that is passed into the previous recursive step).
// After we find the node to remove (if it is in the tree) everything else is the same, we  
// handle the three cases: leaf, one child (which consist of two cases: left vs right),
// and two children.  With iterative algorithm there were subcases regardling if the 
// node was root or not, with recursion we get that for free.  
//
// In the iterative algorithm discussed in class, in dealing with a node with two children
// We swapped values from one of the nodes in either subtree.  For the recursive algorithm
// We just want to write the subtree node's value into the node to be deleted, not actually 
// swap. This way subtree remains a valid bst, so we can recurse on that subtree and 
// recursively call _deleteNode on that value (not the original) to remove that node.  
// 
// It takes a bit to wrap your head around this, use the 6 steps, draw lots of pictures.
// 
BinarySearchTree::Node*	BinarySearchTree::deleteNode(Node *node, int value) {
	Node* ptr;
	if (node == nullptr)
		return nullptr;
	else if (node->value == value) {
		ptr = node;
		if (node->left != nullptr) {
			node->value = maxNode(node->left)->value;
			ptr = deleteNode(node->left, maxNode(node->left)->value);
			if (ptr == nullptr) {
				node->left = nullptr;
			}
		}
		else if (node->right != nullptr) {
			node->value = minNode(node->right)->value;
			ptr = deleteNode(node->right, minNode(node->right)->value);
			if (ptr == nullptr) {
				node->right = nullptr;
			}
		}
		else {
			delete node;
			return nullptr;
		}
	}
	else if (value < node->value) {
		ptr=deleteNode(node->left, value);
		if (ptr == nullptr) {
			node->left = nullptr;
		}
	}
	else {
		ptr=deleteNode(node->right, value);
		if (ptr == nullptr) {
			node->right = nullptr;
		}
	}
	return node;
}


