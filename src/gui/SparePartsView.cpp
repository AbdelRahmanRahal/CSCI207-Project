#include <stack>
#include <QInputDialog>
#include <QLabel>
#include <QVBoxLayout>

#include "LLSupplierDialog.h"
#include "SparePartDialog.h"
#include "SparePartsView.h"


SparePartsView::SparePartsView(QWidget *parent) : QWidget(parent) {
	// Create a QLineEdit for the search bar
	searchLineEdit = new QLineEdit(this);
	searchLineEdit->setPlaceholderText("Search for spare part or number... (e.g., Cylinder, 1234)");
	searchLineEdit->setClearButtonEnabled(true);

	QAction *action = new QAction(this);
	action->setIcon(QIcon("../assets/search.png"));
	searchLineEdit->addAction(action, QLineEdit::LeadingPosition);
	connect(
		searchLineEdit,
		&QLineEdit::textChanged,
		this,
		&SparePartsView::filterSparePartsTree
	);

	// Create a QTreeView for the BST
	sparePartsTreeView = new QTreeView(this);
	sparePartsModel = new QStandardItemModel();

	// Populate the model with the nodes from the BST
	sparePartsTreeView->setModel(sparePartsModel);
	sparePartsTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	sparePartsTreeView->setHeaderHidden(true);
	updateSparePartsTree();

	// Create a QVBoxLayout for the spare parts tree view and its search bar
	QVBoxLayout* sparePartsLayout = new QVBoxLayout;
	sparePartsLayout->addWidget(searchLineEdit);
	sparePartsLayout->addWidget(sparePartsTreeView);

	suppliersTreeView = new QTreeView(this);
	suppliersModel = new QStandardItemModel(this);
	suppliersTreeView->setModel(suppliersModel);
	suppliersTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	suppliersModel->setHorizontalHeaderLabels(QStringList() << "Suppliers at selected spare part:");
	connect(
		sparePartsTreeView,
		&QTreeView::clicked,
		this,
		&SparePartsView::displaySuppliers
	);

	// Create a QVBoxLayout for the suppliers tree view
	QVBoxLayout* suppliersLayout = new QVBoxLayout;
	suppliersLayout->addWidget(suppliersTreeView);

	// Create a QHBoxLayout for the spare parts and suppliers layouts
	QHBoxLayout* treesLayout = new QHBoxLayout;
	treesLayout->addLayout(sparePartsLayout);
	treesLayout->addLayout(suppliersLayout);

	// Create QPushButtons for add and delete
	addSparePartButton = new QPushButton("Add Spare Part", this);
	connect(
		addSparePartButton,
		&QPushButton::clicked,
		this,
		&SparePartsView::addSparePart
	);

	deleteSparePartButton = new QPushButton("Delete Spare Part", this);
	connect(
		deleteSparePartButton,
		&QPushButton::clicked,
		this,
		&SparePartsView::deleteSparePart
	);

	addSupplierButton = new QPushButton("Add Supplier", this);
	connect(
		addSupplierButton,
		&QPushButton::clicked,
		this,
		&SparePartsView::addSupplier
	);

	deleteSupplierButton = new QPushButton("Delete Supplier", this);
	connect(
		deleteSupplierButton,
		&QPushButton::clicked,
		this,
		&SparePartsView::deleteSupplier
	);

	// Create a QHBoxLayout for the buttons
	QHBoxLayout* buttonsLayout = new QHBoxLayout;
	buttonsLayout->addWidget(addSparePartButton);
	buttonsLayout->addWidget(deleteSparePartButton);
	buttonsLayout->addWidget(addSupplierButton);
	buttonsLayout->addWidget(deleteSupplierButton);

	// Add all layouts to one QVBoxLayout
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(treesLayout);
	mainLayout->addLayout(buttonsLayout);

	// Set the layout for the SparePartsView widget
	this->setLayout(mainLayout);
}


void SparePartsView::updateSparePartsTree() {
	sparePartsModel->clear();
	QStandardItem *parentItem = sparePartsModel->invisibleRootItem();
	QStandardItem *item;

	std::stack<BSTNode<SparePart, SupplierNode>*> stack;
	BSTNode<SparePart, SupplierNode>* current = sparePartsBST.root();

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

		SparePart currentData = current->data().record();
		item = new QStandardItem(QString::fromStdString(currentData.name()));
		parentItem->appendRow(item);
		QList<QStandardItem*> childItems;

		QStandardItem *number = new QStandardItem(
			QString("Number: %0").arg(currentData.code())
		);
		QStandardItem *cost = new QStandardItem(
			QString("Cost: %0").arg(currentData.cost())
		);
		QStandardItem *existingParts = new QStandardItem(
			QString("Existing parts: %0").arg(currentData.existingParts())
		);
		childItems.append(number);
		childItems.append(cost);
		childItems.append(existingParts);

		item->appendColumn(childItems);

		// Visit the right subtree
		current = current->right();
	}
}


void SparePartsView::filterSparePartsTree(const QString &text) {
	// Iterate over the items in the model
	for (int i = 0; i < sparePartsModel->rowCount(); ++i) {
		QStandardItem *item = sparePartsModel->item(i);
		// Get the name and code of the item
		QString name = item->text();
		QString code = item->child(0)->text().split(": ").last(); // Assuming the code is the first child and is in the format "Number: <code>"
		// Hide or show the item based on whether its name or code matches the search text
		if (name.contains(text, Qt::CaseInsensitive) || code.contains(text, Qt::CaseInsensitive))
			sparePartsTreeView->setRowHidden(i, QModelIndex(), false);
		else
			sparePartsTreeView->setRowHidden(i, QModelIndex(), true);
	}
}


void SparePartsView::displaySuppliers(const QModelIndex &index) {
	suppliersModel->clear();
	suppliersModel->setHorizontalHeaderLabels(QStringList() << "Suppliers at selected spare part:");

	QStandardItem *item = sparePartsModel->itemFromIndex(index);

	if (item->rowCount() > 0) { // Checking if the item has any children
		unsigned code = item->child(0)->text().split(": ").last().toUInt();
		BSTNode<SparePart, SupplierNode> *sparePartNode = sparePartsBST.search(code);

		if (sparePartNode != nullptr) {
			SupplierNode *supplierNode = sparePartNode->data().head();
			while (supplierNode != nullptr) {
				QStandardItem *supplierItem = new QStandardItem(
					QString::fromStdString(supplierNode->data().name())
				);
				suppliersModel->appendRow(supplierItem);

				QStandardItem *codeItem = new QStandardItem(
					QString("Code: %0").arg(supplierNode->data().code())
				);
				QStandardItem *addressItem = new QStandardItem(
					QString("Address: %0").arg(QString::fromStdString(supplierNode->data().address()))
				);
				QStandardItem *telephoneItem = new QStandardItem(
					QString("Telephone: %0").arg(QString::fromStdString(supplierNode->data().telephone()))
				);
				QStandardItem *emailItem = new QStandardItem(
					QString("Email: %0").arg(QString::fromStdString(supplierNode->data().email()))
				);

				supplierItem->appendRow(codeItem);
				supplierItem->appendRow(addressItem);
				supplierItem->appendRow(telephoneItem);
				supplierItem->appendRow(emailItem);

				supplierNode = supplierNode->next();
			}
		}
	}
}


void SparePartsView::addSparePart() {
	// Show a QInputDialog to get the required data for the new node,
	// check if a node with the given code already exists, and if not,
	// insert the new node into the binary tree and update the model.
	SparePartDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) {
		unsigned number = dialog.getNumber();
		std::string name = dialog.getName();
		double cost = dialog.getCost();
		unsigned existingParts = dialog.getExistingParts();

		SparePart newSparePart(name, number, cost, existingParts);
		LinkedList<SparePart, SupplierNode> newData(newSparePart);

		if (!sparePartsBST.insert(newData)) {
			QMessageBox::information(
				this,
				tr("Error"),
				tr("A spare part with the same code already exists.")
			);
			string logMessage = "❌ Failed to add spare part: a supplier with the same number (" +
								std::to_string(number) +
								") already exists.";
			log(QString::fromStdString(logMessage));
			return;
		}

		updateSparePartsTree();

		string logMessage = "✅ Added spare part: " + name + " (" + std::to_string(number) + ")";
		log(QString::fromStdString(logMessage));
	}
}


void SparePartsView::deleteSparePart() {
	// Show a QInputDialog to get the code of the node to remove
	bool ok;
	unsigned number = QInputDialog::getInt(
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
		// Check if a node with the given code exists, and if so, remove it from the binary tree
		if (!sparePartsBST.remove(number)) {
			QMessageBox::information(
				this,
				tr("Error"),
				tr("A spare part with the given number does not exist.")
			);
			string logMessage = "❌ Failed to delete spare part: A spare part with the given number (" +
								std::to_string(number) +
								") does not exist.";
			return;
		}

		updateSparePartsTree();

		string logMessage = "⛔ Removed spare part number " + std::to_string(number) + ".";
		log(QString::fromStdString(logMessage));
	}
}


void SparePartsView::addSupplier() {
	// Get the selected item
	QStandardItem *item = sparePartsModel->itemFromIndex(sparePartsTreeView->currentIndex());

	// If no item is selected, show an error message
	if (item == nullptr) {
		QMessageBox::information(this, tr("Error"), tr("No spare part selected."));
		return;
	}

	// Get the spare part from the binary search tree
	unsigned number = item->child(0)->text().split(": ").last().toUInt();
	BSTNode<SparePart, SupplierNode>* sparePartNode = sparePartsBST.search(number);

	// If the spare part was found, show a dialog to get the supplier data and add it to the spare part's linked list
	if (sparePartNode != nullptr) {
		LLSupplierDialog dialog(this);
		if (dialog.exec() == QDialog::Accepted) {
			std::string name = dialog.getName();
			unsigned code = dialog.getCode();
			std::string address = dialog.getAddress();
			std::string telephone = dialog.getTelephone();
			std::string email = dialog.getEmail();

			Supplier newSupplier(name, code, address, telephone, email);
			SupplierNode* newNode = new SupplierNode(newSupplier);

			sparePartNode->data().insert(newNode);
			displaySuppliers(sparePartsTreeView->currentIndex());

			string logMessage = "✅ Added supplier to " +
								sparePartNode->data().record().name() +
								": " + name + " (" + std::to_string(code) + ")";
			log(QString::fromStdString(logMessage));
		}
	}
}


void SparePartsView::deleteSupplier() {
	// Get the selected item
	QStandardItem *item = sparePartsModel->itemFromIndex(sparePartsTreeView->currentIndex());

	// If no item is selected, show an error message
	if (item == nullptr) {
		QMessageBox::information(this, tr("Error"), tr("No spare part selected."));
		return;
	}

	// Get the spare part from the binary search tree
	unsigned code = item->child(0)->text().split(": ").last().toUInt();
	BSTNode<SparePart, SupplierNode>* sparePartNode = sparePartsBST.search(code);

	// If the spare part was found, show a dialog to get the supplier code and delete it from the spare part's linked list
	if (sparePartNode != nullptr) {
		bool ok;
		unsigned supplierCode = QInputDialog::getInt(
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
			if (sparePartNode->data().remove(supplierCode)) {
				displaySuppliers(sparePartsTreeView->currentIndex());

				string logMessage = "⛔ Removed supplier with code " +
									std::to_string(supplierCode) +
									" from " + sparePartNode->data().record().name();
				log(QString::fromStdString(logMessage));
			}
			else {
				QMessageBox::information(
					this,
					tr("Error"),
					tr("No supplier with the given code found.")
				);
				string logMessage = "❌ Failed to delete supplier: A supplier with the given code (" +
									std::to_string(supplierCode) +
									") does not exist.";
				log(QString::fromStdString(logMessage));
			}

			displaySuppliers(sparePartsTreeView->currentIndex());
		}
	}
}
