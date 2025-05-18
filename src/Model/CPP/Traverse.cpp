#include "traverse.h"
#include "ui_traverse.h"

Traverse::Traverse(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Traverse)
{
    ui->setupUi(this);

}
/*Traverse::Traverse(vector<BfsNode*>cityGraphics,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Traverse)
{
    ui->setupUi(this);
    this->cityGraphics=cityGraphics;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(170, 10, 781, 541);
    ui->graphicsView->setScene(scene);
    QStringList iconPaths = {
        "D:/Test/city1.png"
        "D:/Test/city2.png",
        "D:/Test/city3.png",
        "D:/Test/city4.png",
        "D:/Test/city5.png",
        "D:/Test/city6.png",
        "D:/Test/city7.png",
        "D:/Test/city8.png",
        "D:/Test/city9.png",
        "D:/Test/city10.png",
        "D:/Test/city11.png",
        "D:/Test/city12.png",
        "D:/Test/city13.png",
        "D:/Test/city14.png",
        "D:/Test/city15.png",
        "D:/Test/city16.png",
        "D:/Test/city17.png",
        "D:/Test/city18.png",
        "D:/Test/city19.png",
        "D:/Test/city20.png",
        "D:/Test/city21.png"
    };


    for(auto it:cityGraphics){
        qDebug()<<it->indx;
        QPixmap cityIcon(iconPaths[it->indx]);
        cityIcon = cityIcon.scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem* item = scene->addPixmap(cityIcon);
        item->setPos(QPointF(400, 140));
        QGraphicsTextItem* label = scene->addText(QString::fromStdString(it->name));
        label->setPos(400 , 115);
        QFont font("Segoe UI", 12, QFont::Bold);
        font.setItalic(true);
        font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
        label->setFont(font);
        label->setDefaultTextColor(Qt::darkBlue);

        QGraphicsItemGroup* group = scene->createItemGroup({ item, label });
        group->setFlag(QGraphicsItem::ItemIsMovable);
    }


    ui->graphicsView->setMouseTracking(true);
    ui->graphicsView->viewport()->setMouseTracking(true);
    ui->graphicsView->viewport()->installEventFilter(this);


}
*/


Traverse::Traverse(Graph *g, unordered_map<string, int>  cityGraphics, string root,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Traverse)
{

    ui->setupUi(this);
    qDebug() << g->getName();
    this->g = g;
    this->cityGraphics = cityGraphics;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(170, 10, 781, 541);
    ui->graphicsView->setScene(scene);
    iconPaths = {
        "D:/Test/city1.png",
        "D:/Test/city2.png",
        "D:/Test/city3.png",
        "D:/Test/city4.png",
        "D:/Test/city5.png",
        "D:/Test/city6.png",
        "D:/Test/city7.png",
        "D:/Test/city8.png",
        "D:/Test/city9.png",
        "D:/Test/city10.png",
        "D:/Test/city11.png",
        "D:/Test/city12.png",
        "D:/Test/city13.png",
        "D:/Test/city14.png",
        "D:/Test/city15.png",
        "D:/Test/city16.png",
        "D:/Test/city17.png",
        "D:/Test/city18.png",
        "D:/Test/city19.png",
        "D:/Test/city20.png",
        "D:/Test/city21.png"
    };
    computeLeaves(root);
     drawNodes(QPointF(500,50),root);
}
bool Traverse::eventFilter(QObject* obj, QEvent* event) {
    if (obj == ui->graphicsView->viewport() && event->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF scenePos2 = ui->graphicsView->mapToScene(mouseEvent->pos());
        QString posText = QString("X: %1, Y: %2")
                              .arg(scenePos2.x(), 0, 'f', 2)
                              .arg(scenePos2.y(), 0, 'f', 2);


     QToolTip::showText(mouseEvent->globalPosition().toPoint(), posText);




    }

    return QDialog::eventFilter(obj, event);

}

int Traverse::computeLeaves(string root)
{   vis[root]=true;
    if(g->nodes[root]->edges.size()<=1)
        return leaves[root]=1;
    int ans=0;
    for(auto it :g->nodes[root]->edges)
    {
        string child=(g->edges[it]->source==root?g->edges[it]->destination:g->edges[it]->source);
        if(!vis[child])
        ans+=computeLeaves(child);


    }
    return leaves[root]=ans;

}

void Traverse::drawNodes(QPointF point, string node)
{
    visDraw[node]=true;
    QPixmap cityIcon(iconPaths[cityGraphics[node]]);
    cityIcon = cityIcon.scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsTextItem* label = scene->addText(QString::fromStdString(node));
    label->setPos(point+QPointF(0,-25));

    QFont font("Segoe UI", 12, QFont::Bold);
    font.setItalic(true);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
    label->setFont(font);
    label->setDefaultTextColor(Qt::darkBlue);

    QGraphicsPixmapItem* item = scene->addPixmap(cityIcon);
    item->setPos(point);

    QGraphicsItemGroup* group = scene->createItemGroup({ item, label });
    group->setFlag(QGraphicsItem::ItemIsMovable);

    int left=point.x()-(leaves[node]*space);
    for(auto it:g->nodes[node]->edges) {
        string child=(g->edges[it]->source==node?g->edges[it]->destination:g->edges[it]->source);

        if(visDraw[child])continue;
        int childX=left+leaves[child]*space;
        int childY=point.y()+2*space;

        QPointF childPoint(childX,childY);
        animatedLine = scene->addLine(QLineF(point + QPointF(50, 50), childPoint + QPointF(50, 50)), QPen(Qt::blue, 2, Qt::DashLine));
        animatedLine->setZValue(-1);
        // qDebug()<<point.x()<<" "<<childPoint.x()<<"\n";
        drawNodes(childPoint,child);
        left+=leaves[child]*2*space;
    }

}


Traverse::~Traverse()
{
    delete ui;
}

void Traverse::on_ok_Putton_clicked()
{
    this->close();
}

