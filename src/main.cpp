/*

	---------- Team Members ----------
	AbdelRahman Rahal		221001443
	Mahmoud AbdelGelil		221001313
	Merna AbdelWahab		221001684
	Mohamed AbdelRaouf		221001609

*/


#include <iostream>

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
	void setNumber(int number) { m_partNumber = number; }
	void setCost(double cost) { m_cost = cost; }
	void setExistingParts(unsigned existingParts) { m_existingParts = existingParts; }

	// Member functions
	void getData() const {
		cout << endl;
		cout << "------------------------------" << endl;
		cout << "Spare part:\t" << name() << endl;
		cout << "Part number:\t" << number() << endl;
		cout << "Part cost:\t" << cost() << endl;
		cout << "Existing parts:\t" << existingParts() << endl;
	}

	void putData() {
//		cout << "Spare part name:\t";
//		getline(cin, m_partName);
	}

	void modifyData() {
		// Modify spare part information
	}
};
int main() {
	cout << "Hello, world!" << endl;
	return 0;
}
