#pragma once
#include <QMainWindow>
#include "ui_HomePage.h"
#include "GraphPage.h"

class HomePage : public QMainWindow
{
	Q_OBJECT

public:
	HomePage(QWidget *parent = nullptr);
	~HomePage();
private slots:
	void addGraphButtonSlot();
	void logoutButtonSlot();
	void updateGraphs();
    void on_historyButton_clicked();
private:
	Ui::HomePageClass ui;
};
