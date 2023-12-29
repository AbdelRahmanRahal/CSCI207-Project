#include "LogDisplay.h"
#include "SupplierDialog.h"
#include "mainwindow.h"
#include "BST.h"
#include "Supplier.h"
#include "SparePartNode.h"
#include <stack>
#include <QLabel>
#include <QPushButton>
#include <QTabWidget>
#include <QTabBar>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QStackedWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setMinimumSize(720, 480);

	// Create a QTabBar and a QStackedWidget
	QTabBar* tabBar = new QTabBar(this);
	QStackedWidget* stackedWidget = new QStackedWidget(this);

	// Create two tabs
	QWidget* suppliersTab = new QWidget();
	QWidget* sparePartsTab = new QWidget();

	// Add the tabs to the QTabBar and the QStackedWidget
	tabBar->addTab("Suppliers");
	tabBar->addTab("Spare Parts");
	stackedWidget->addWidget(suppliersTab);
	stackedWidget->addWidget(sparePartsTab);

	// Connect the currentChanged signal of the QTabBar to the setCurrentIndex slot of the QStackedWidget
	connect(tabBar, &QTabBar::currentChanged, stackedWidget, &QStackedWidget::setCurrentIndex);

	// Create a QVBoxLayout and add the QTabBar and the QStackedWidget to it
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(tabBar);
	layout->addWidget(stackedWidget);

	// Create a QLineEdit for the search bar
	searchLineEdit = new QLineEdit(this);
	connect(searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::filterNodes);

	// Create a QTreeView for the binary tree
	treeView = new QTreeView(this);
	model = new QStandardItemModel();

	// Populate the model with the nodes from your binary tree
	treeView->setModel(model);
	treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	treeView->setHeaderHidden(true);
	updateSupplierTree();

	// displayNodeData() is supposed to show the data inside of the linkedlist of each binary tree node when you click on it
//	connect(treeView, &QTreeView::clicked, this, &MainWindow::displayNodeData);

	// Create QPushButton for insert and delete
	insertButton = new QPushButton("Insert", this);
	connect(insertButton, &QPushButton::clicked, this, &MainWindow::insertNode);

	deleteButton = new QPushButton("Delete", this);
	connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteNode);


	// Create a QVBoxLayout and add the QLabel, QPushButton, and QTextEdit to it
	QVBoxLayout* suppliersLayout = new QVBoxLayout;
	suppliersLayout->addWidget(searchLineEdit);
	suppliersLayout->addWidget(treeView);
	suppliersLayout->addWidget(insertButton);
	suppliersLayout->addWidget(deleteButton);

	// Set the layout of the "Suppliers" tab to the QVBoxLayout
	suppliersTab->setLayout(suppliersLayout);

	// Create a QTextEdit for the log area
	LogDisplay* logDisplay = new LogDisplay(this);
	logDisplay->appendMessage("This is a log message");

	// Add the LogDisplay to the QVBoxLayout
	layout->addWidget(logDisplay);

	// Create a QWidget, set its layout to the QVBoxLayout, and set it as the central widget of the MainWindow
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
}

void MainWindow::updateSupplierTree() {
	model->clear();
	QStandardItem *parentItem = model->invisibleRootItem();
	QStandardItem *item;

	std::stack<BSTNode<Supplier, SparePartNode>*> stack;
	BSTNode<Supplier, SparePartNode>* current = supplierBST.root();

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


void MainWindow::filterNodes(const QString &text) {
	// Iterate over the items in the model and hide or show them based on whether they match the search text
}

void MainWindow::insertNode() {
	// Show a QInputDialog to get the required data for the new node, check if a node with the given code already exists, and if not, insert the new node into the binary tree and update the model
	SupplierDialog dialog(this);
	if (dialog.exec() == QDialog::Accepted) {
		unsigned code = dialog.getCode();
		std::string name = dialog.getName();
		std::string address = dialog.getAddress();
		std::string telephone = dialog.getTelephone();
		std::string email = dialog.getEmail();

		Supplier newSupplier(name, code, address, telephone, email);
		LinkedList<Supplier, SparePartNode> newData(newSupplier);

		if (!supplierBST.insert(newData)) {
			QMessageBox::information(this, tr("Error"),
									 tr("A supplier with the same code already exists."));
			return;
		}

		updateSupplierTree();
	}
}

void MainWindow::deleteNode() {
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
		if (!supplierBST.remove(code)) {
			QMessageBox::information(
					this,
					tr("Error"),
					tr("A supplier with the given code does not exist.")
					);
			return;
		}

		// Update the model
		updateSupplierTree();
	}
}