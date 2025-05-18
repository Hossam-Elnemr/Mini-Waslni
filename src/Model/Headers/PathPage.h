#pragma once

#include <QDialog>
#include "ui_PathPage.h"
using namespace std;
class PathPage : public QDialog
{
    Q_OBJECT

public:
    PathPage(QWidget* parent = nullptr, vector<string>path = {},string graphName="");
    void start();
    ~PathPage();

private:
    Ui::PathPageClass ui;
    QGraphicsScene* scene;
    vector<string>path;
    string graphName;
};
