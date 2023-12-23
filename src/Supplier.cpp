#include "Supplier.h"


void Supplier::getData() const {
	cout << endl;
	cout << "------------------------------" << endl;
	cout << "Supplier:\t" << name() << endl;
	cout << "Supplier code:\t" << code() << endl;
	cout << "Address:\t" << address() << endl;
	cout << "Telephone:\t" << telephone() << endl;
	cout << "Email:\t\t" << email() << endl;
}


void Supplier::putData() {
	string name, address, telephone, email;
	unsigned code;

	cout << endl;
	cout << "------------------------------" << endl;
	cout << "Enter the required data." << endl;

	cout << "Supplier:\t";
	getline(cin, name);

	cout << "Supplier code:\t";
	cin >> code;
	cin.ignore();

	cout << "Address:\t";
	getline(cin, address);

	cout << "Telephone:\t";
	getline(cin, telephone);

	cout << "Email:\t\t";
	getline(cin, email);

	setName(name);
	setCode(code);
	setAddress(address);
	setTelephone(telephone);
	setEmail(email);
}