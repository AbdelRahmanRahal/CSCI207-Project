#ifndef CSCI207_PROJECT_SPAREPART_H
#define CSCI207_PROJECT_SPAREPART_H

#include <iostream>
#include <string>

using std::cin,
      std::cout,
      std::endl,
      std::string;


class SparePart {
private:
	string m_partName;
	unsigned m_partNumber;
	double m_cost;
	unsigned m_existingParts;

public:
	// Getters
	/*
		Following the naming convention for getters of only using
		"get...()" with functions that return a calculated/processed
		value, and otherwise using a shorthand name of the attribute.
		https://cginternals.github.io/guidelines/articles/getter-setter-naming/
	*/
	string name() const { return m_partName; }
	unsigned number() const { return m_partNumber; }
	double cost() const { return m_cost; }
	unsigned existingParts() const { return m_existingParts; }

	// Setters
	void setName(string &name) { m_partName = name; }
	void setNumber(unsigned number) { m_partNumber = number; }
	void setCost(double cost) { m_cost = cost; }
	void setExistingParts(unsigned existingParts) { m_existingParts = existingParts; }

	// Member functions
	void getData() const;

	void putData();

	void modifyData(); // TODO: Implement method
};


#endif //CSCI207_PROJECT_SPAREPART_H
