#ifndef CSCI207_PROJECT_SUPPLIERSVIEW_H
#define CSCI207_PROJECT_SUPPLIERSVIEW_H

#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTreeView>
#include <QWidget>

#include "../BST.h"
#include "../Supplier.h"
#include "../SparePartNode.h"


class SuppliersView : public QWidget {
Q_OBJECT

private:
	QLineEdit *searchLineEdit;
	QTreeView *suppliersTreeView;
	QStandardItemModel *suppliersModel;
	QTreeView *sparePartsTreeView;
	QStandardItemModel *sparePartsModel;
	QPushButton *addSupplierButton;
	QPushButton *deleteSupplierButton;
	QPushButton *addSparePartButton;
	QPushButton *deleteSparePartButton;
	BST<Supplier, SparePartNode> suppliersBST;

public:
	explicit SuppliersView(QWidget *parent = nullptr);
	void updateSuppliersTree();
	void filterSuppliersTree(const QString &text);
	void displaySpareParts(const QModelIndex &index);
	void addSupplier();
	void deleteSupplier();
	void addSparePart();
	void deleteSparePart();
};



#endif //CSCI207_PROJECT_SUPPLIERSVIEW_H
