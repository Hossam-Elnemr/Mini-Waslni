#include "HomePage.h"
#include"GraphPage.h"
#include"LoginPage.h"
#include<QInputDialog>
#include<QGraphicsDropShadowEffect>
#include<QVBoxLayout>
// Manager m = Manager::getInstance();
HomePage::HomePage(QWidget *parent)
	: QMainWindow(parent)
{
    cerr << "Hooooooooooooomeeeeeeeeee\n";
	ui.setupUi(this);
	QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
	shadow->setBlurRadius(15);
	shadow->setOffset(0, 4);
	shadow->setColor(QColor(0, 0, 0, 80));
	ui.cardWidget->setGraphicsEffect(shadow);

    //addGraph
    connect(ui.addGraphButton, &QPushButton::clicked, this, &HomePage::addGraphButtonSlot);
    connect(ui.logoutButton, &QPushButton::clicked, this, &HomePage::logoutButtonSlot);

    updateGraphs();

}
void HomePage::updateGraphs() {
    QVBoxLayout* layout = new QVBoxLayout(ui.graphListContainer);
    ui.graphListContainer->setLayout(layout);

    QVBoxLayout* layout2 = new QVBoxLayout(ui.graphListContainer_2);
    ui.graphListContainer_2->setLayout(layout2);
    for (auto g : Manager::getInstance()->graphs){
        QPushButton* btn = new QPushButton(QString::fromStdString(g->getName()));
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #ffa31a;
                color: white;
                border-radius: 10px;
                padding: 10px 16px;
                letter-spacing: 2px;
                font-weight: bold;
                font-size:20px;
            }
            QPushButton:hover {
                background-color: #ff8c00;
            }
        )");

        layout->addWidget(btn);
        cout << "\nBefore Button\n";
        connect(btn, &QPushButton::clicked, this, [=]() {
            GraphPage* gp = new GraphPage(g);
            gp->show();
        });
    }
    cerr << "here: " << Manager::curUser->userName << ' ' << Manager::curUser->getpassword();
    cerr << Manager::curUser->graphsId.size() << '\n';
    for (auto gID : Manager::curUser->graphsId)
    {
        Graph* g = Manager::getInstance()->findGraph(gID, "");
        cerr << gID << ' ' << Manager::getInstance()->graphs.size() << '\n';
        cerr << "graph: " << (g == nullptr) << '\n';
        QPushButton* btn = new QPushButton(QString::fromStdString(g->getName()));
        cerr << "done\n";
        btn->setStyleSheet(R"(
            QPushButton {
            background-color: rgb(0, 188, 209);
            color: white;
            border-radius: 10px;
            padding: 10px 16px;
            letter-spacing: 2px;
            font-weight: bold;
            font-size:20px;
        }
        QPushButton:hover {
            background-color: rgb(0, 170, 220);
        }
        )");

        layout2->addWidget(btn);

        connect(btn, &QPushButton::clicked, this, [=]() {
            GraphPage* gp = new GraphPage(g);
            gp->show();
        });
    }
}








void HomePage::logoutButtonSlot() {
    LoginPage* login = new LoginPage;
    login->show();
    this->close();
}
void HomePage::addGraphButtonSlot() {
    bool ok;
    QString text = QInputDialog::getText(this, "Enter Graph Name", "Graph name:", QLineEdit::Normal, "", &ok);
    string name = text.toStdString();

    if (!ok || text.isEmpty())
        return;
    if(!Tools::validateName(name, this)) {
        return;
    }

    if (text.isEmpty()) {
        QMessageBox::information(this, "empty input", "Please Enter a Graph Name.");
        return;
    }
    for (auto c : text.toStdString()) {
        if (Tools::isSpecialChar(c)) {
            QMessageBox::information(this, "Invalid Input", "Please enter a graph name that doesn't contain special characters.");
            return;
        }
    }
    if(Manager::getInstance()->findGraph(-1, name) != NULL) {
        QMessageBox::warning(this, "Name was Found", "Enter another name!!");
        return;
    }
    Manager::getInstance()->addGraph(name);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui.graphListContainer->layout());
    QVBoxLayout* layout2 = qobject_cast<QVBoxLayout*>(ui.graphListContainer_2->layout());
    QPushButton* btn = new QPushButton(text);
    QPushButton* btn2 = new QPushButton(text);
    btn->setStyleSheet(R"(
        QPushButton {
            background-color: #ffa31a;
            color: white;
            border-radius: 10px;
            padding: 10px 16px;
            letter-spacing: 2px;
            font-weight: bold;
            font-size:20px;
        }
        QPushButton:hover {
            background-color: #ff8c00;
        }
    )");
    btn2->setStyleSheet(R"(
        QPushButton {
            background-color: rgb(0, 188, 209);
            color: white;
            border-radius: 10px;
            padding: 10px 16px;
            letter-spacing: 2px;
            font-weight: bold;
            font-size:20px;
        }
        QPushButton:hover {
            background-color: rgb(0, 170, 220);
        }
    )");
    layout->addWidget(btn);
    layout2->addWidget(btn2);

    connect(btn, &QPushButton::clicked, this, [=]() {
        GraphPage* gp = new GraphPage(Manager::getInstance()->findGraph(-1,text.toStdString()));
        gp->show();
    });
}
void HomePage::on_historyButton_clicked()
{
    History* h = new History(Manager::curUser, this);
    h->show();
}
HomePage::~HomePage()
{}
