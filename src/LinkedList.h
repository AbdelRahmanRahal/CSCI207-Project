#ifndef CSCI207_PROJECT_LINKEDLIST_H
#define CSCI207_PROJECT_LINKEDLIST_H


template <class Record, class Node>
class LinkedList {
private:
	Record record;
	Node* head;

public:
	explicit LinkedList(Record record, Node* head = nullptr)
	: record(record), head(head) {}

	// Function to add a new node at the end of the list
	void insert(Node* node) {
		// If the list is empty, make the new node the head
		if (head == nullptr) {
			head = node;
		}
		else {
			Node* temp = head;
			while (temp->next() != nullptr) {
				temp = temp->next();
			}
			temp->setNext(node);
		}
	}

	// Function to delete a node from the list
	void remove(Node* node) {
		// If the list is empty, do nothing
		if (head == nullptr) return;

		// If the head node is the one to delete
		if (head == node) {
			Node* temp = head;
			head = head->next();
			delete temp;
			return;
		}

		// Otherwise, search for the node to delete
		Node* temp = head;
		while (temp->next() != nullptr && temp->next() != node) {
			temp = temp->next();
		}

		// If the node was found, delete it
		if (temp->next() != nullptr) {
			Node* toDelete = temp->next();
			temp->setNext(temp->next()->next());
			delete toDelete;
		}
	}

	// Function to print all nodes in the list
	void printList() {
		Node* temp = head;
		while (temp != nullptr) {
			temp->data().getData(); // Assuming SparePart and Supplier classes have getData() to print their data
			temp = temp->next();
		}
	}
};

#endif //CSCI207_PROJECT_LINKEDLIST_H
