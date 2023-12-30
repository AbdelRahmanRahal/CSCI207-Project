#include <QVBoxLayout>

#include "mainwindow.h"
#include "SparePartsView.h"
#include "SuppliersView.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setMinimumSize(720, 480);

	// Create a QTabBar and a QStackedWidget
	tabBar = new QTabBar(this);
	stackedWidget = new QStackedWidget(this);

	// Create two tabs
	suppliersTab = new QWidget();
	sparePartsTab = new QWidget();

	// Add the tabs to the QTabBar and the QStackedWidget
	tabBar->addTab("Suppliers");
	tabBar->addTab("Spare Parts");
	stackedWidget->addWidget(suppliersTab);
	stackedWidget->addWidget(sparePartsTab);

	// Connect the currentChanged signal of the QTabBar to the setCurrentIndex slot of the QStackedWidget
	connect(
		tabBar,
		&QTabBar::currentChanged,
		stackedWidget,
		&QStackedWidget::setCurrentIndex
	);

	// Create a QVBoxLayout and add the QTabBar and the QStackedWidget to it
	QVBoxLayout* layout = new QVBoxLayout;
	layout->addWidget(tabBar);
	layout->addWidget(stackedWidget);

	// Set the layout of the suppliers tab to the QVBoxLayout
	QVBoxLayout* suppliersLayout = new QVBoxLayout;
	suppliersLayout->addWidget(new SuppliersView);
	suppliersTab->setLayout(suppliersLayout);

	// Set the layout of the spare parts tab to the QVBoxLayout
	QVBoxLayout* sparePartsLayout = new QVBoxLayout;
	sparePartsLayout->addWidget(new SparePartsView);
	sparePartsTab->setLayout(sparePartsLayout);

	// Create a QTextEdit for the log area
	logDisplay = new LogDisplay(this);
	logDisplay->appendMessage("This is a log message.");

	// Add the LogDisplay to the QVBoxLayout
	layout->addWidget(logDisplay);

	// Create a QWidget, set its layout to the QVBoxLayout, and set it as the central widget of the MainWindow
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(layout);
	setCentralWidget(centralWidget);
}