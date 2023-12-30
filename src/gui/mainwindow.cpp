#include <QTime>
#include <QTimer>
#include <QVBoxLayout>

#include "mainwindow.h"
#include "SparePartsView.h"
#include "SuppliersView.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	setMinimumSize(720, 480);
	setWindowIcon(QIcon(":/assets/icon.png"));

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
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabBar);
	mainLayout->addWidget(stackedWidget);

	// Instantiate suppliersView and sparePartsView
	suppliersView = new SuppliersView;
	connect(
		suppliersView,
		&SuppliersView::log,
		this,
		&MainWindow::log
	);

	sparePartsView = new SparePartsView;
	connect(
		sparePartsView,
		&SparePartsView::log,
		this,
		&MainWindow::log
	);

	// Set the layout of the suppliers tab to the QVBoxLayout
	QVBoxLayout* suppliersLayout = new QVBoxLayout;
	suppliersLayout->addWidget(suppliersView);
	suppliersTab->setLayout(suppliersLayout);

	// Set the layout of the spare parts tab to the QVBoxLayout
	QVBoxLayout* sparePartsLayout = new QVBoxLayout;
	sparePartsLayout->addWidget(sparePartsView);
	sparePartsTab->setLayout(sparePartsLayout);

	// Create a QTextEdit for the log area
	logDisplay = new LogDisplay(this);

	// Create a QPushButton for the "Dump Log" button
	dumpLogButton = new QPushButton("Dump Log", this);
	connect(
		dumpLogButton,
		&QPushButton::clicked,
		this,
		&MainWindow::dumpLog
	);

	// Create a QPushButton for the "Clear Log" button
	clearLogButton = new QPushButton("Clear Log", this);
	connect(
		clearLogButton,
		&QPushButton::clicked,
		this,
		&MainWindow::clearLog
	);

	// Create a QVBoxLayout and the 2 log buttons to it
	QVBoxLayout* logButtonsLayout = new QVBoxLayout;
	logButtonsLayout->addWidget(dumpLogButton);
	logButtonsLayout->addWidget(clearLogButton);

	// Create a QHBoxLayout and add logDisplay and logButtonsLayout to it
	QHBoxLayout* logLayout = new QHBoxLayout;
	logLayout->addWidget(logDisplay);
	logLayout->addLayout(logButtonsLayout);

	// Add logLayout to mainLayout
	mainLayout->addLayout(logLayout);

	// Create a QWidget, set its layout to the QVBoxLayout, and set it as the central widget of the MainWindow
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);
}


void MainWindow::log(const QString& message) {
	QString timestamp = QTime::currentTime().toString("h:mm AP");
	QString formattedMessage = QString("%1 [%2]").arg(message, timestamp);
	logStack.push(formattedMessage);
}


void MainWindow::dumpLog() {
	if (logStack.empty()) {
		logDisplay->appendMessage("⚠️ Log is empty.");
		QTimer::singleShot(2000, this, [this]() {
			QTextCursor cursor(logDisplay->document());
			cursor.movePosition(QTextCursor::End);
			cursor.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
			cursor.movePosition(QTextCursor::PreviousCharacter, QTextCursor::KeepAnchor);
			cursor.removeSelectedText();
		});
	}
	else
		while (!logStack.empty()) {
			logDisplay->appendMessage(logStack.top());
			logStack.pop();
		}
}


void MainWindow::clearLog() {
	logDisplay->clear();
}