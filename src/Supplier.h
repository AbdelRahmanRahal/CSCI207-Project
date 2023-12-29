#ifndef CSCI207_PROJECT_SUPPLIER_H
#define CSCI207_PROJECT_SUPPLIER_H

#include <iostream>
#include <string>

using std::cin,
      std::cout,
      std::endl,
      std::string;

class Supplier {
private:
	string m_supplierName;
	unsigned m_supplierCode;
	string m_address;
	string m_telephone;
	string m_email;

public:
	// Constructors
	Supplier(string name, unsigned code, string address, string telephone, string email)
	:	m_supplierName(name),
		m_supplierCode(code),
		m_address(address),
		m_telephone(telephone),
		m_email(email) {}

	Supplier() = default;

	// Getters
	string name() const { return m_supplierName; }
	unsigned code() const { return m_supplierCode; }
	string address() const { return m_address; }
	string telephone() const { return m_telephone; }
	string email() const { return m_email; }

	// Setters
	void setName(string &name) { m_supplierName = name; }
	void setCode(unsigned code) { m_supplierCode = code; }
	void setAddress(string &address) { m_address = address; }
	void setTelephone(string &telephone) { m_telephone = telephone; }
	void setEmail(string &email) { m_email = email; }

	// Member functions
	void getData() const;

	void putData();

	void modifyData(); // TODO: Implement method
};


#endif //CSCI207_PROJECT_SUPPLIER_H
