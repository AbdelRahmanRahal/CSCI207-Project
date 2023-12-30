#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

#include "LogDisplay.h"
#include "SparePartsView.h"
#include "SuppliersView.h"
#include "../Stack.h"


class MainWindow : public QMainWindow {
Q_OBJECT

private:
	QTabBar* tabBar;
	QStackedWidget* stackedWidget;
	QWidget* suppliersTab;
	QWidget* sparePartsTab;
	SuppliersView* suppliersView;
	SparePartsView* sparePartsView;
	LogDisplay* logDisplay;
	QPushButton* dumpLogButton;
	QPushButton* clearLogButton;
	Stack logStack; // The stack for storing log messages

public:
	explicit MainWindow(QWidget *parent = nullptr);

public slots:
	void log(const QString& message);
	void dumpLog();
	void clearLog();

};

#endif // MAINWINDOW_H