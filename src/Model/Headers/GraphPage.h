#pragma once
#include "history.h"
#include "traverse.h"
#include "PathFinder.h"
#include <QMainWindow>
#include<qgraphicsscene.h>
#include "DataSaver.cpp"
#include "PathPage.h"

class GraphPage : public QMainWindow
{
	Q_OBJECT

public:
    unordered_map<string, pair<int, int>>positions;
	QPointF getCityPosition(const QString& cityName);
	QMap<QString, QGraphicsItemGroup*> cityGroups;
	QVector<pair<QGraphicsLineItem*, Edge*>>edges;
    unordered_map<string, int> cityGraphics; // {nodeName, index of picture}
    stack <tuple<int, string, vector<Edge*>>> lastOperations;

	Graph* graph;
    int inOperation = 0;
    bool isUndo = false; // says if that operation came from undo or not
	GraphPage(Graph* g, QWidget* parent = nullptr);
    void displayGraph();
	~GraphPage();

    //								  Modify graph
	void addCity();
    void addCity(string cityName);
    void addEdge();
    void deleteCity();
    void deleteEdge();

    //                                Requests
    void  findTour();
    void findShortest();
    void findFastest();
    void undo();

    //                                Our Helpers

	void drawAnimatedLine(const QPointF& start, const QPointF& end, QString name, QString from, QString to);
	bool eventFilter(QObject* obj, QEvent* event) override;

public slots:
    void on_find_Bridge_clicked();
private slots:

    void on_pushButton_8_clicked();
    void on_startTraverse_clicked();
    void on_traverseNode_clicked();

private:
	QGraphicsScene* scene;
	QMap<QString, QPointF> cityPositions;
	QGraphicsLineItem* animatedLine;
	Ui::GraphPageClass ui;
};
