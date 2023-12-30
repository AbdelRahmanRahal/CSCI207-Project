#ifndef CSCI207_PROJECT_SPAREPARTSVIEW_H
#define CSCI207_PROJECT_SPAREPARTSVIEW_H

#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>
#include <QWidget>

#include "../BST.h"
#include "../SparePart.h"
#include "../SupplierNode.h"


class SparePartsView : public QWidget {
Q_OBJECT

private:
	QLineEdit *searchLineEdit;
	QTreeView *sparePartsTreeView;
	QStandardItemModel *sparePartsModel;
	QTreeView *suppliersTreeView;
	QStandardItemModel *suppliersModel;
	QPushButton *addSparePartButton;
	QPushButton *deleteSparePartButton;
	QPushButton *addSupplierButton;
	QPushButton *deleteSupplierButton;
	BST<SparePart, SupplierNode> sparePartsBST;

public:
	explicit SparePartsView(QWidget *parent = nullptr);
	void updateSparePartsTree();
	void filterSparePartsTree(const QString &text);
	void displaySuppliers(const QModelIndex &index);
	void addSparePart();
	void deleteSparePart();
	void addSupplier();
	void deleteSupplier();

signals:
	void log(const QString& message);
};

#endif //CSCI207_PROJECT_SPAREPARTSVIEW_H
