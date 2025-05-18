#include "History.h"

History::History(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(100);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setStyleSheet(
        "QTableWidget {"
        "    background-color: #f0f0f0;"
        //"    gridline-color: #d3d3d3;"
        "    font-size: 14px;"
        "    border: 1px solid #a0a0a0;"
        "}"
        "QHeaderView::section {"
        "    background-color: #3e878a;"
        "    color: white;"
        "    padding: 5px;"
        "    border: 1px solid #6c6c6c;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #3399ff;"
        "    color: white;"
        "}"
        );
    for (int i = 0; i < 100; i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString("rehab")));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString("sobhy")));

    }

}
History::History(User* u, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::History)
{
    ui->setupUi(this);
    this->user = u;
    ui->tableWidget->setRowCount(user->recentSearch.size());
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setStyleSheet(
        "QTableWidget {"
        "    background-color: #f0f0f0;"
        "    gridline-color: #d3d3d3;"
        "    font-size: 14px;"
        "}"
        "QHeaderView::section {"
        "    background-color: #3e878a;"
        "    color: white;"
        "    padding: 5px;"
        "    border: 1px solid #6c6c6c;"
        "}"
        "QTableWidget::item:selected {"
        "    background-color: #3399ff;"
        "    color: white;"
        "}"
        );
    stack<pair<string, string>>search = user->recentSearch;

    for (int i = 0; i < user->recentSearch.size(); i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(search.top().first)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(search.top().second)));
        search.pop();

    }


}

History::~History()
{
    delete ui;
}
