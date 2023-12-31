#ifndef CSCI207_PROJECT_BST_H
#define CSCI207_PROJECT_BST_H

#include "BSTNode.h"
#include "LinkedList.h"

template <class Record, class Node>
class BST {
private:
	BSTNode<Record, Node>* m_root;

public:
	// Constructor
	explicit BST(BSTNode<Record, Node>* root = nullptr) : m_root(root) {}

	// Getters
	BSTNode<Record, Node>* root() { return m_root; }

	// Setters
	void setRoot(BSTNode<Record, Node>* root) { m_root = root; }


	// Inserting a node
	// Time complexity: O(log n)
	bool insert(LinkedList<Record, Node> data) {
		BSTNode<Record, Node>* newNode = new BSTNode<Record, Node>(data);

		if (root() == nullptr) {
			setRoot(newNode);
			return true;
		}
		else {
			BSTNode<Record, Node>* parent = nullptr;
			BSTNode<Record, Node>* curr = root();

			while (curr != nullptr) {
				if (data.record().code() == curr->data().record().code()) {
					// Node with same code already exists
					delete newNode;
					return false;
				}
				parent = curr;
				if (data.record().code() < curr->data().record().code())
					curr = curr->left();
				else
					curr = curr->right();
			}

			if (data.record().code() < parent->data().record().code())
				parent->setLeft(newNode);
			else
				parent->setRight(newNode);
			return true;
		}
	}


	// Searching for a node
	// Time complexity: O(log n)
	BSTNode<Record, Node>* search(unsigned code) {
		BSTNode<Record, Node>* curr = root();

		while (curr != nullptr)
			if (code == curr->data().record().code())
				return curr;
			else if (code < curr->data().record().code())
				curr = curr->left();
			else
				curr = curr->right();

		return nullptr; // Return null if the node is not found
	}


	// Deleting a node
	// Time complexity: O(log n)
	bool remove(unsigned code) {
		BSTNode<Record, Node>* parent = nullptr;
		BSTNode<Record, Node>* curr = root();
		bool isLeftChild = false;

		// Search for the node to be deleted
		while (curr != nullptr) {
			if (code == curr->data().record().code())
				break;
			parent = curr;
			if (code < curr->data().record().code()) {
				isLeftChild = true;
				curr = curr->left();
			} else {
				isLeftChild = false;
				curr = curr->right();
			}
		}

		// Return false if the node with the given code is not found
		if (curr == nullptr)
			return false;

		// Node with only one child or no child
		if (curr->left() == nullptr || curr->right() == nullptr) {
			BSTNode<Record, Node>* temp = curr->left() ? curr->left() : curr->right();

			// No child case
			if (temp == nullptr) {
				if (curr == root()) {
					setRoot(nullptr);
				} else {
					if (isLeftChild)
						parent->setLeft(nullptr);
					else
						parent->setRight(nullptr);
				}
			} else { // One child case
				if (curr == root()) {
					setRoot(temp);
				} else {
					if (isLeftChild)
						parent->setLeft(temp);
					else
						parent->setRight(temp);
				}
			}

			delete curr;
		} else { // Node with two children: get the inorder successor (smallest in the right subtree)
			BSTNode<Record, Node>* temp = minValueNode(curr->right());
			curr->setData(temp->data());
			curr->setRight(deleteNodeHelper(curr->right(), temp->data().record().code()));
		}

		return true;
	}


	// Time complexity: O(log n)
	BSTNode<Record, Node>* deleteNodeHelper(BSTNode<Record, Node>* root, unsigned key) {
		if (root == nullptr) return root;

		// If the key to be deleted is smaller than the root's key,
		// then it lies in left subtree
		if (key < root->data().record().code())
			root->setLeft(deleteNodeHelper(root->left(), key));

			// If the key to be deleted is greater than the root's key,
			// then it lies in right subtree
		else if (key > root->data().record().code())
			root->setRight(deleteNodeHelper(root->right(), key));

			// if key is same as root's key, then this is the node to be deleted
		else {
			// node with only one child or no child
			if (root->left() == nullptr) {
				BSTNode<Record, Node>* temp = root->right();
				delete root;
				return temp;
			} else if (root->right() == nullptr) {
				BSTNode<Record, Node>* temp = root->left();
				delete root;
				return temp;
			}

			// node with two children: get the inorder successor (smallest in the right subtree)
			BSTNode<Record, Node>* temp = minValueNode(root->right());

			// copy the inorder successor's content to this node
			root->setData(temp->data());

			// delete the inorder successor
			root->setRight(deleteNodeHelper(root->right(), temp->data().record().code()));
		}
		return root;
	}


	// Finding the minimum node
	// Time complexity: O(h); h = the height of the subtree rooted at the node passed
	BSTNode<Record, Node>* minValueNode(BSTNode<Record, Node>* node = nullptr) {
		// Cannot set root() as the default parameter, so this does the job.
		if (node == nullptr)
			node = root();

		BSTNode<Record, Node>* curr = node;

		while (curr && curr->left() != nullptr)
			curr = curr->left();

		return curr;
	}


	// Finding the maximum node
	// Time complexity: O(h); h = the height of the subtree rooted at the node passed
	BSTNode<Record, Node>* maxValueNode(BSTNode<Record, Node>* node = nullptr) {
		if (node == nullptr)
			node = root();

		BSTNode<Record, Node>* curr = node;

		while (curr && curr->right() != nullptr)
			curr = curr->right();

		return curr;
	}
};


#endif //CSCI207_PROJECT_BST_H
