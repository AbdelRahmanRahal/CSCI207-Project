/*

	---------- Team Members ----------
	AbdelRahman Rahal		221001443
	Mahmoud AbdelGelil		221001313
	Merna AbdelWahab		221001684
	Mohamed AbdelRaouf		221001609

*/

#include "gui/mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
