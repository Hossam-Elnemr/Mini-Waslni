#pragma once
#ifndef TRAVERSE_H
#define TRAVERSE_H

#include <QDialog>
#include "Globals.h"
#include "bfsNode.h"
#include <QPixmap>
#include <QGraphicsScene>
#include<qgraphicsscene.h>
#include<QRandomGenerator>
#include<QGraphicsTextItem>
#include<qtimer.h>
#include<qmessagebox.h>
#include <QToolTip>
#include <QPropertyAnimation>
#include <Qobject>
#include <QGraphicsView>
#include <QDebug>
#include  <Qstring>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <Qstring>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QPen>
#include<QtCore>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QPoint>
#include <QPainterPath>
#include <QPolygon>
#include <QVector>
#include <QWidget>
#include <QToolTip>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include<QGraphicsDropShadowEffect>
#include "Graph.h"
#include <QPointF>

namespace Ui {
class Traverse;
}

class Traverse : public QDialog
{
    Q_OBJECT

public:
     Traverse(QWidget *parent = nullptr);
   // Traverse(vector<BfsNode*>cityGraphics,QWidget *parent = nullptr);
     Traverse(Graph* g,unordered_map<string, int> cityGraphics,string root,QWidget *parent = nullptr);
    ~Traverse();

    QStringList iconPaths;
    const int space=70;
    Graph* g;


    unordered_map<string,int>cityGraphics;
    unordered_map<string ,int >leaves;
    unordered_map<string,bool>vis;
    unordered_map<string,bool>visDraw;

    bool eventFilter(QObject* obj, QEvent* event) override;
    int computeLeaves(string root);
    void drawNodes(QPointF point,string node);

private slots:
    void on_ok_Putton_clicked();

private:
    Ui::Traverse *ui;
    QGraphicsScene *scene;
    QGraphicsLineItem* animatedLine;

};

#endif // TRAVERSE_H
