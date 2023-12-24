//
// Created by Robin PC on 23/12/2023.
//

#ifndef CSCI207_PROJECT_SPAREPARTNODE_H
#define CSCI207_PROJECT_SPAREPARTNODE_H

#include "SparePart.h"


class SparePartNode {
private:
	SparePart m_data;
	SparePartNode* m_next;

public:
	// Constructor
	explicit SparePartNode(SparePart &data, SparePartNode* next = nullptr)
	:	m_data(data),
		m_next(next) {}

	// Getters
	SparePart& data() { return m_data; }
	SparePartNode* next() { return m_next; }

	// Setters
	void setData(SparePart& data) { m_data = data; }
	void setNext(SparePartNode* next) { m_next = next; }
};


#endif //CSCI207_PROJECT_SPAREPARTNODE_H
