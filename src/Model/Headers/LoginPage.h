#pragma once

#include <QMainWindow>
#include <QMessageBox>
#include<QPainter.h>
#include<qpainterpath.h>
#include "ui_LoginPage.h"
#include "HomePage.h"
# include "DataLoader.h"

class LoginPage : public QMainWindow
{
	Q_OBJECT

public:
	LoginPage(QWidget *parent = nullptr);
	~LoginPage();

private slots:
    void Login();
    void SignUp();
	void on_togglePasswordButton_clicked();
    
private:
	Ui::LoginPageClass ui;
	bool isPasswordVisible = false;
};
