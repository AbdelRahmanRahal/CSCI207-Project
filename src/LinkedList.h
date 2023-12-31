#ifndef CSCI207_PROJECT_LINKEDLIST_H
#define CSCI207_PROJECT_LINKEDLIST_H


template <class Record, class Node>
class LinkedList {
private:
	Record m_record;
	Node* m_head;

public:
	explicit LinkedList(Record &record, Node* head = nullptr)
	:	m_record(record),
		m_head(head) {}

	// Getters
	Record& record() { return m_record; }
	Node* head() { return m_head; }

	// Setters
	void setRecord(Record& record) { m_record = record; }
	void setHead(Node* head) { m_head = head; }

	// Function to add a new node at the end of the list
	void insert(Node* node) {
		// If the list is empty, make the new node the head
		if (head() == nullptr)
			setHead(node);
		else {
			Node* temp = head();
			while (temp->next() != nullptr)
				temp = temp->next();

			temp->setNext(node);
		}
	}

	// Function to delete a node from the list
	bool remove(unsigned code) {
		// Start from the head of the list
		Node* temp = head();

		// If the list is empty, do nothing
		if (temp == nullptr) return false;

		// If the node to delete is the head node
		if (temp->data().code() == code) {
			Node* toDelete = temp;
			setHead(temp->next());
			delete toDelete;
			return true;
		}

		// Otherwise, find the node to delete
		while (temp->next() != nullptr && temp->next()->data().code() != code)
			temp = temp->next();

		// If the node was found, delete it
		if (temp->next() != nullptr) {
			Node* toDelete = temp->next();
			temp->setNext(temp->next()->next());
			delete toDelete;
			return true;
		}

		// If the node was not found, return false
		return false;
	}
};

#endif //CSCI207_PROJECT_LINKEDLIST_H
