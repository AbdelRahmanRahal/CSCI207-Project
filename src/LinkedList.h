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
	void remove(Node* node) {
		// If the list is empty, do nothing
		if (head() == nullptr) return;

		// If the head node is the one to delete
		if (head() == node) {
			Node* temp = head();
			setHead(head()->next());
			delete temp;
			return;
		}

		// Otherwise, search for the node to delete
		Node* temp = head();
		while (temp->next() != nullptr && temp->next() != node)
			temp = temp->next();

		// If the node was found, delete it
		if (temp->next() != nullptr) {
			Node* toDelete = temp->next();
			temp->setNext(temp->next()->next());
			delete toDelete;
		}
	}
};

#endif //CSCI207_PROJECT_LINKEDLIST_H
