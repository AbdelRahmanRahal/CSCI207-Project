/*

	---------- Team Members ----------
	AbdelRahman Rahal		221001443
	Mahmoud AbdelGelil		221001313
	Merna AbdelWahab		221001684
	Mohamed AbdelRaouf		221001609

*/

#include "BST.h"
#include "BSTNode.h"
#include "mainwindow.h"
#include "LinkedList.h"
#include "SparePartNode.h"
#include "SparePart.h"
#include "Supplier.h"
#include <QApplication>
#include <iostream>

using std::cin,
      std::cout,
      std::endl,
      std::string;


int main(int argc, char *argv[]) {
//	QApplication a(argc, argv);
//	MainWindow w;
//	w.show();
//	return a.exec();

//	cout << "Hello, world!" << endl;
//	THESE ARE NOT PERMANENT AND ARE ONLY TO TEST MY IMPLEMENTATIONS SO FAR
	cout << "Welcome!" << endl;

	// Create some SparePart objects
	SparePart sparePart1 = SparePart();
	sparePart1.putData();

	SparePart sparePart2 = SparePart();
	sparePart2.putData();

	SparePart sparePart3 = SparePart();
	sparePart3.putData();

	// Create some SparePartNode objects
	SparePartNode* sparePartNode1 = new SparePartNode(sparePart1);
	SparePartNode* sparePartNode2 = new SparePartNode(sparePart2);
	SparePartNode* sparePartNode3 = new SparePartNode(sparePart3);

	// Create some Supplier objects
	Supplier supplier1 = Supplier();
	supplier1.putData();

	Supplier supplier2 = Supplier();
	supplier2.putData();

	// Create some LinkedList objects
	LinkedList<Supplier, SparePartNode> LL1 = LinkedList<Supplier, SparePartNode>(supplier1);
	LL1.insert(sparePartNode1);
	LL1.insert(sparePartNode2);

	LinkedList<Supplier, SparePartNode> LL2 = LinkedList<Supplier, SparePartNode>(supplier2);
	LL2.insert(sparePartNode2);
	LL2.insert(sparePartNode3);

	// Create a BST object
	BST<Supplier, SparePartNode> bst;

	// Insert LinkedLists into the BST
	bst.insert(LL1);
	bst.insert(LL2);

	// Search for a LinkedList in the BST
	unsigned codeToSearch = 101;
	BSTNode<Supplier, SparePartNode>* foundNode = bst.search(codeToSearch);
	if (foundNode != nullptr) {
		cout << "Found LinkedList with code " << codeToSearch << endl;
		foundNode->data().record().getData();
	} else {
		cout << "LinkedList with code " << codeToSearch << " not found." << endl;
	}

	// Find the minimum and maximum LinkedLists in the BST
	BSTNode<Supplier, SparePartNode>* minNode = bst.minValueNode();
	cout << endl;
	cout << "Minimum LinkedList: " << minNode->data().record().code() << endl;
	minNode->data().printList();

	BSTNode<Supplier, SparePartNode>* maxNode = bst.maxValueNode();
	cout << endl;
	cout << "Maximum LinkedList: " << maxNode->data().record().code() << endl;
	maxNode->data().printList();

	// TODO: Add test cases for delete and update methods after they are implemented

	getchar();
	return 0;
}
