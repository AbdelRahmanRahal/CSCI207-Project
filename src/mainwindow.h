#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "BST.h"
#include "BSTNode.h"
#include "SparePart.h"
#include "SparePartNode.h"
#include "Supplier.h"
#include "SupplierNode.h"
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>

class MainWindow : public QMainWindow
{
Q_OBJECT

private:
	QStandardItemModel *model;
	QTreeView *treeView;
	QLineEdit *searchLineEdit;
	QPushButton *insertButton;
	QPushButton *deleteButton;
	BST<Supplier, SparePartNode> supplierBST;
	BST<SparePart, SupplierNode> sparePartBST;

public:
	explicit MainWindow(QWidget *parent = nullptr);
	void updateSupplierTree();
	void filterNodes(const QString &text);
	void insertNode();
	void deleteNode();
};

#endif // MAINWINDOW_H