#pragma once

#include <QMainWindow>
#include "ui_History.h"
#include"Manager.h"
#include "User.h"

class History : public QMainWindow
{
    Q_OBJECT

public:
    User* user;
    History(QWidget *parent = nullptr);
    History(User* u, QWidget* parent = nullptr);
    ~History();

private:
    Ui::History *ui;
};
