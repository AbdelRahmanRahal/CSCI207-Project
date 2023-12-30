#include <stack>
#include <QInputDialog>
#include <QLabel>
#include <QVBoxLayout>

#include "LLSparePartDialog.h"
#include "SupplierDialog.h"
#include "SuppliersView.h"


SuppliersView::SuppliersView(QWidget *parent) : QWidget(parent) {
	// Create a QLineEdit for the search bar
	searchLineEdit = new QLineEdit(this);
	searchLineEdit->setPlaceholderText("Search for supplier or code... (e.g., Michelin, 1234)");
	searchLineEdit->setClearButtonEnabled(true);

	QAction *action = new QAction(this);
	action->setIcon(QIcon("../assets/search.png"));
	searchLineEdit->addAction(action, QLineEdit::LeadingPosition);
	connect(
		searchLineEdit,
		&QLineEdit::textChanged,
		this,
		&SuppliersView::filterSuppliersTree
	);

	// Create a QTreeView for the BST
	suppliersTreeView = new QTreeView(this);
	suppliersModel = new QStandardItemModel();

	// Populate the model with the nodes from the BST
	suppliersTreeView->setModel(suppliersModel);
	suppliersTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	suppliersTreeView->setHeaderHidden(true);
	updateSuppliersTree();

	// Create a QVBoxLayout for the supplierS tree view and its search bar
	QVBoxLayout* suppliersLayout = new QVBoxLayout;
	suppliersLayout->addWidget(searchLineEdit);
	suppliersLayout->addWidget(suppliersTreeView);

	sparePartsTreeView = new QTreeView(this);
	sparePartsModel = new QStandardItemModel(this);
	sparePartsTreeView->setModel(sparePartsModel);
	sparePartsTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	sparePartsModel->setHorizontalHeaderLabels(QStringList() << "Spare parts at selected supplier:");
	connect(
		suppliersTreeView,
		&QTreeView::clicked,
		this,
		&SuppliersView::displaySpareParts
	);

	// Create a QVBoxLayout for the spare parts tree view
	QVBoxLayout* sparePartsLayout = new QVBoxLayout;
	sparePartsLayout->addWidget(sparePartsTreeView);

	// Create a QHBoxLayout for the supplierS and spare parts layouts
	QHBoxLayout* treesLayout = new QHBoxLayout;
	treesLayout->addLayout(suppliersLayout);
	treesLayout->addLayout(sparePartsLayout);

	// Create QPushButtons for add and delete
	addSupplierButton = new QPushButton("Add Supplier", this);
	connect(
		addSupplierButton,
		&QPushButton::clicked,
		this,
		&SuppliersView::addSupplier
	);

	deleteSupplierButton = new QPushButton("Delete Supplier", this);
	connect(
		deleteSupplierButton,
		&QPushButton::clicked,
		this,
		&SuppliersView::deleteSupplier
	);

	addSparePartButton = new QPushButton("Add Spare Part", this);
	connect(
		addSparePartButton,
		&QPushButton::clicked,
		this,
		&SuppliersView::addSparePart
	);

	deleteSparePartButton = new QPushButton("Delete Spare Part", this);
	connect(
		deleteSparePartButton,
		&QPushButton::clicked,
		this,
		&SuppliersView::deleteSparePart
	);

	// Create a QHBoxLayout for the buttons
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(addSupplierButton);
	buttonsLayout->addWidget(deleteSupplierButton);
	buttonsLayout->addWidget(addSparePartButton);
	buttonsLayout->addWidget(deleteSparePartButton);

	// Add all layouts to one QVBoxLayout
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(treesLayout);
	mainLayout->addLayout(buttonsLayout);

	// Set the layout for the SuppliersView widget
	this->setLayout(mainLayout);
}


void SuppliersView::updateSuppliersTree() {
	suppliersModel->clear();
	QStandardItem *parentItem = suppliersModel->invisibleRootItem();
	QStandardItem *item;

	std::stack<BSTNode<Supplier, SparePartNode>*> stack;
	BSTNode<Supplier, SparePartNode>* current = suppliersBST.root();

	// In-order traversal of the BST
	while (current != nullptr || !stack.empty()) {
		// Reach the leftmost node of the current node
		while (current != nullptr) {
			stack.push(current);
			current = current->left();
		}

		// Current must be nullptr at this point
		current = stack.top();
		stack.pop();

		Supplier currentData = current->data().record();
		item = new QStandardItem(QString::fromStdString(currentData.name()));
		parentItem->appendRow(item);
		QList<QStandardItem*> childItems;

		QStandardItem *code = new QStandardItem(
			QString("Code: %0").arg(currentData.code())
		);
		QStandardItem *address = new QStandardItem(
			QString("Address: %0").arg(QString::fromStdString(currentData.address()))
		);
		QStandardItem *telephone = new QStandardItem(
			QString("Telephone: %0").arg(QString::fromStdString(currentData.telephone()))
		);
		QStandardItem *email = new QStandardItem(
			QString("Email: %0").arg(QString::fromStdString(currentData.email()))
		);
		childItems.append(code);
		childItems.append(address);
		childItems.append(telephone);
		childItems.append(email);

		item->appendColumn(childItems);

		// Visit the right subtree
		current = current->right();
	}
}


void SuppliersView::filterSuppliersTree(const QString &text) {
	// Iterate over the items in the model
	for (int i = 0; i < suppliersModel->rowCount(); ++i) {
		QStandardItem *item = suppliersModel->item(i);
		// Get the name and code of the item
		QString name = item->text();
		QString code = item->child(0)->text().split(": ").last(); // Assuming the code is the first child and is in the format "Code: <code>"
		// Hide or show the item based on whether its name or code matches the search text
		if (name.contains(text, Qt::CaseInsensitive) || code.contains(text, Qt::CaseInsensitive))
			suppliersTreeView->setRowHidden(i, QModelIndex(), false);
		else
			suppliersTreeView->setRowHidden(i, QModelIndex(), true);
	}
}


void SuppliersView::displaySpareParts(const QModelIndex &index) {
	sparePartsModel->clear();
	sparePartsModel->setHorizontalHeaderLabels(QStringList() << "Spare parts at selected supplier:");

	QStandardItem *item = suppliersModel->itemFromIndex(index);

	if (item->rowCount() > 0) { // Checking if the item has any children
		unsigned code = item->child(0)->text().split(": ").last().toUInt();
		BSTNode<Supplier, SparePartNode> *supplierNode = suppliersBST.search(code);

		if (supplierNode != nullptr) {
			SparePartNode *sparePartNode = supplierNode->data().head();
			while (sparePartNode != nullptr) {
				QStandardItem *sparePartItem = new QStandardItem(
					QString::fromStdString(sparePartNode->data().name())
				);
				sparePartsModel->appendRow(sparePartItem);

				QStandardItem *numberItem = new QStandardItem(
					QString("Number: %0").arg(sparePartNode->data().code())
				);
				QStandardItem *costItem = new QStandardItem(
					QString("Cost: %0").arg(sparePartNode->data().cost())
				);
				QStandardItem *existingPartsItem = new QStandardItem(
					QString("Existing parts: %0").arg(sparePartNode->data().existingParts())
				);

				sparePartItem->appendRow(numberItem);
				sparePartItem->appendRow(costItem);
				sparePartItem->appendRow(existingPartsItem);

				sparePartNode = sparePartNode->next();
			}
		}
	}
}


void SuppliersView::addSupplier() {
	// Show a QInputDialog to get the required data for the new node,
	// check if a node with the given code already exists, and if not,
	// insert the new node into the binary tree and update the model.
	SupplierDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) {
		unsigned code = dialog.getCode();
		std::string name = dialog.getName();
		std::string address = dialog.getAddress();
		std::string telephone = dialog.getTelephone();
		std::string email = dialog.getEmail();

		Supplier newSupplier(name, code, address, telephone, email);
		LinkedList<Supplier, SparePartNode> newData(newSupplier);

		if (!suppliersBST.insert(newData)) {
			QMessageBox::information(
				this,
				tr("Error"),
				tr("A supplier with the same code already exists.")
			);
			return;
		}

		updateSuppliersTree();
	}
}


void SuppliersView::deleteSupplier() {
	// Show a QInputDialog to get the code of the node to remove
	bool ok;
	unsigned code = QInputDialog::getInt(
		this,
		tr("Delete Supplier"),
		tr("Enter the code of the supplier to delete:"),
		0,
		0,
		INT_MAX,
		1,
		&ok
	);
	if (ok) {
		// Check if a node with the given code exists, and if so, remove it from the binary tree
		if (!suppliersBST.remove(code)) {
			QMessageBox::information(
				this,
				tr("Error"),
				tr("A supplier with the given code does not exist.")
			);
			return;
		}

		// Update the model
		updateSuppliersTree();
	}
}


void SuppliersView::addSparePart() {
	// Get the selected item
	QStandardItem *item = suppliersModel->itemFromIndex(suppliersTreeView->currentIndex());

	// If no item is selected, show an error message
	if (item == nullptr) {
		QMessageBox::information(this, tr("Error"), tr("No supplier selected."));
		return;
	}

	// Get the supplier from the binary search tree
	unsigned code = item->child(0)->text().split(": ").last().toUInt();
	BSTNode<Supplier, SparePartNode>* supplierNode = suppliersBST.search(code);

	// If the supplier was found, show a dialog to get the spare part data and add it to the supplier's linked list
	if (supplierNode != nullptr) {
		LLSparePartDialog dialog(this);
		if (dialog.exec() == QDialog::Accepted) {
			std::string name = dialog.getName();
			unsigned number = dialog.getNumber();
			double cost = dialog.getCost();
			unsigned existingParts = dialog.getExistingParts();

			SparePart newSparePart(name, number, cost, existingParts);
			SparePartNode* newNode = new SparePartNode(newSparePart);

			supplierNode->data().insert(newNode);
			displaySpareParts(suppliersTreeView->currentIndex());
		}
	}
}


void SuppliersView::deleteSparePart() {
	// Get the selected item
	QStandardItem *item = suppliersModel->itemFromIndex(suppliersTreeView->currentIndex());

	// If no item is selected, show an error message
	if (item == nullptr) {
		QMessageBox::information(this, tr("Error"), tr("No supplier selected."));
		return;
	}

	// Get the supplier from the binary search tree
	unsigned code = item->child(0)->text().split(": ").last().toUInt();
	BSTNode<Supplier, SparePartNode>* supplierNode = suppliersBST.search(code);

	// If the supplier was found, show a dialog to get the spare part code and delete it from the supplier's linked list
	if (supplierNode != nullptr) {
		bool ok;
		unsigned sparePartCode = QInputDialog::getInt(
			this,
			tr("Delete Spare Part"),
			tr("Enter the number of the spare part to delete:"),
			0,
			0,
			INT_MAX,
			1,
			&ok
		);
		if (ok) {
			SparePartNode* prevNode = nullptr;
			SparePartNode* currNode = supplierNode->data().head();
			while (currNode != nullptr && currNode->data().code() != sparePartCode) {
				prevNode = currNode;
				currNode = currNode->next();
			}
			if (currNode != nullptr) {
				if (prevNode == nullptr)
					supplierNode->data().setHead(currNode->next());
				else
					prevNode->setNext(currNode->next());

				delete currNode;
				displaySpareParts(suppliersTreeView->currentIndex());
			} else
				QMessageBox::information(
					this,
					tr("Error"),
					tr("No spare part with the given number found.")
				);

			displaySpareParts(suppliersTreeView->currentIndex());
		}
	}
}