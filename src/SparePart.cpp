#include "SparePart.h"


void SparePart::getData() const {
	cout << endl;
	cout << "------------------------------" << endl;
	cout << "Spare part:\t" << name() << endl;
	cout << "Part number:\t" << code() << endl;
	cout << "Part cost:\t" << cost() << endl;
	cout << "Existing parts:\t" << existingParts() << endl;
}


void SparePart::putData() {
	string name;
	unsigned number, existingParts;
	double cost;

	cout << endl;
	cout << "------------------------------" << endl;
	cout << "Enter the required data." << endl;

	cout << "Spare part:\t";
	getline(cin, name);

	cout << "Part number:\t";
	cin >> number;
	cin.ignore();

	cout << "Part cost:\t";
	cin >> cost;
	cin.ignore();

	cout << "Existing parts:\t";
	cin >> existingParts;
	cin.ignore();

	setName(name);
	setNumber(number);
	setCost(cost);
	setExistingParts(existingParts);
}