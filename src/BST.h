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
	void insert(LinkedList<Record, Node> data) {
		BSTNode<Record, Node>* newNode = new BSTNode<Record, Node>(data);

		if (root() == nullptr)
			setRoot(newNode);
		else {
			BSTNode<Record, Node>* parent = nullptr;
			BSTNode<Record, Node>* curr = root();

			while (curr != nullptr) {
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
		}
	}

	// Searching for a node
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


	// TODO: Implement delete and other necessary methods


	// Finding the minimum node
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
	BSTNode<Record, Node>* maxValueNode(BSTNode<Record, Node>* node = nullptr) {
		if (node == nullptr)
			node = root();

		BSTNode<Record, Node>* curr = node;

		while (curr && curr->right() != nullptr)
			curr = curr->right();

		return curr;
	}
	void deleteNode(unsigned code) {
   deleteNodeHelper(m_root, code);
}

void deleteNodeHelper(BSTNode<Record, Node>*& node, unsigned code) {
   if (node == nullptr) {
       throw std::invalid_argument("Cannot delete a non-existent node.");
   }

   if (code < node->data().record().code()) {
       deleteNodeHelper(node->left(), code);
   } else if (code > node->data().record().code()) {
       deleteNodeHelper(node->right(), code);
   } else {
       if (!node->left() || !node->right()) {
           BSTNode<Record, Node>* temp = node->left() ? node->left() : node->right();

           if (!temp) {
               temp = node;
               node = nullptr;
           } else {
               *node = *temp;
           }

           delete temp;
       } else {
           BSTNode<Record, Node>* temp = minValueNode(node->right());
           node->data() = temp->data();
           deleteNodeHelper(node->right(), temp->data().record().code());
       }
   }
}

void deleteNode(unsigned code) {
    /**
     * Deletes a node with the given code from the BST.
     *
     * @param code the code of the node to be deleted
     */
    deleteNodeHelper(m_root, code);
}


#endif //CSCI207_PROJECT_BST_H
