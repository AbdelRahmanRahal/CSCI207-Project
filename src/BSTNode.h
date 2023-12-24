#ifndef CSCI207_PROJECT_BSTNODE_H
#define CSCI207_PROJECT_BSTNODE_H

#include "LinkedList.h"


template <class Record, class Node>
class BSTNode {
private:
	LinkedList<Record, Node> m_data;
	BSTNode<Record, Node>* m_left;
	BSTNode<Record, Node>* m_right;

public:
	// Constructor
	explicit BSTNode(LinkedList<Record, Node> &data)
	:	m_data(data),
		m_left(nullptr),
		m_right(nullptr) {}

	// Getters
	LinkedList<Record, Node>& data() { return m_data; }
	BSTNode<Record, Node>* left() { return m_left; }
	BSTNode<Record, Node>* right() { return m_right; }

	// Setters
	void setData(LinkedList<Record, Node>& data) { m_data = data; }
	void setLeft(BSTNode<Record, Node>* left) { m_left = left; }
	void setRight(BSTNode<Record, Node>* right) { m_right = right; }
};


#endif //CSCI207_PROJECT_BSTNODE_H
