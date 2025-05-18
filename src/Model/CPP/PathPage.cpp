#include "PathPage.h"
#include"Manager.h"
#include"Graph.h"
#include<QPropertyAnimation>
#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QPointF>
#include<qdebug.h>
PathPage::PathPage(QWidget* parent, vector<string>path,string graphName)
    : QDialog(parent), path(path),graphName(graphName)
{

    ui.setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(170, 10, 781, 541);
    QPixmap background("mapbg.jpg");
    QPixmap scaledBg = background.scaled(scene->sceneRect().size().toSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scene->setBackgroundBrush(QBrush(scaledBg));
    ui.graphicsView->setScene(scene);
    qDebug() << "path i: " << path[0];
    qDebug() << "g name: " << graphName;
    start();
}
void PathPage::start() {
    Graph* graph = Manager::getInstance()->findGraph(-1, graphName);
    QStringList iconPaths = {
        "city1.png",
        "city2.png",
        "city3.png",
        "city4.png",
        "city5.png",
        "city6.png",
        "city7.png",
        "city8.png",
        "city9.png",
        "city10.png",
        "city11.png",
        "city12.png",
        "city13.png",
        "city14.png",
        "city15.png",
        "city16.png",
        "city17.png",
        "city18.png",
        "city19.png",
        "city20.png",
        "city21.png"
    };
    int d = 850 / path.size();
    for (int i = 0; i < path.size(); i++) {
        int x;
        (i == 0) ? x = 200 : x = 200+(i) * d;
        QPixmap cityIcon(iconPaths[graph->nodes[path[i]]->iconId]);
        cityIcon = cityIcon.scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        QGraphicsPixmapItem* item = scene->addPixmap(cityIcon);
        item->setPos(QPointF(x, 230));
        QGraphicsTextItem* label = scene->addText(QString::fromStdString(path[i]));
        label->setPos(x, 210 );

        QFont font("Segoe UI", 12, QFont::Bold);
        font.setItalic(true);
        font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
        label->setFont(font);
        label->setDefaultTextColor(Qt::darkBlue);

        QGraphicsItemGroup* group = scene->createItemGroup({ item, label });
        group->setFlag(QGraphicsItem::ItemIsMovable);

    }
    QPen pen(Qt::black, 4, Qt::DashLine);
    scene->addLine(QLineF(QPointF(220, 260), QPointF( 220+(path.size()-1) * d, 260)), pen)->setZValue(-1);
    QPropertyAnimation* move = new QPropertyAnimation(ui.car, "geometry");
    move->setDuration(2500);
    move->setStartValue(QRect(50, 100, 100, 60));
    move->setEndValue(QRect(50+(path.size()-1) * d, 100, 100, 60));
    move->start();
}
PathPage::~PathPage()
{}
