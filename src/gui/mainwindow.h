#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

#include "LogDisplay.h"


class MainWindow : public QMainWindow {
Q_OBJECT

private:
	QTabBar* tabBar;
	QStackedWidget* stackedWidget;
	QWidget* suppliersTab;
	QWidget* sparePartsTab;
	LogDisplay* logDisplay;

public:
	explicit MainWindow(QWidget *parent = nullptr);

};

#endif // MAINWINDOW_H