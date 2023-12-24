//
// Created by Robin PC on 23/12/2023.
//

#ifndef CSCI207_PROJECT_SUPPLIERNODE_H
#define CSCI207_PROJECT_SUPPLIERNODE_H

#include "Supplier.h"


class SupplierNode {
private:
	Supplier m_data;
	SupplierNode* m_next;

public:
	// Constructor
	explicit SupplierNode(Supplier &data, SupplierNode* next = nullptr)
	:	m_data(data),
		m_next(next) {}

	// Getters
	Supplier& data() { return m_data; }
	SupplierNode* next() { return m_next; }

	// Setters
	void setData(Supplier& data) { m_data = data; }
	void setNext(SupplierNode* next) { m_next = next; }
};


#endif //CSCI207_PROJECT_SUPPLIERNODE_H
