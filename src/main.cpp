/*

	---------- Team Members ----------
	AbdelRahman Rahal		221001443
	Mahmoud AbdelGelil		221001313
	Merna AbdelWahab		221001684
	Mohamed AbdelRaouf		221001609

*/

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
	Supplier supplier = Supplier();
	supplier.putData();
	supplier.getData();

	SparePart sparePart1 = SparePart();
	sparePart1.putData();
	sparePart1.getData();

	SparePart sparePart2 = SparePart();
	sparePart2.putData();
	sparePart2.getData();

	SparePartNode* sparePartNode1 = new SparePartNode(sparePart1);
	SparePartNode* sparePartNode2 = new SparePartNode(sparePart2);

	LinkedList<Supplier, SparePartNode> LL = LinkedList<Supplier, SparePartNode>(supplier);
	LL.insert(sparePartNode1);
	LL.insert(sparePartNode2);
	LL.printList();

	getchar();
	return 0;
}
