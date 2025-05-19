#include "GraphPage.h"
#include <QIcon>
GraphPage::GraphPage(Graph* g,QWidget *parent) : graph(g), QMainWindow(parent)
{
    ui.setupUi(this);
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    // cerr << "\nGraphPage " << (g == nullptr) << '\n';
    Manager::getInstance()->enterGraph(g);

    shadow->setBlurRadius(15);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 80));
    ui.widget_2->setGraphicsEffect(shadow);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(170, 10, 781, 541);
    QPixmap background("D:/Test//mapBackground.jpg");
    QPixmap scaledBg = background.scaled(scene->sceneRect().size().toSize(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    // cerr << "\nmid\n";
    scene->setBackgroundBrush(QBrush(scaledBg));
    ui.graphicsView->setScene(scene);
    // cerr << "\nbefore\n";
    graph = g;
    displayGraph();
    cerr << "\nafter\n";
    connect(ui.addcity, &QPushButton::clicked, this, [=] {
        addCity();
    });
    // connect(ui.addcity, &QPushButton::clicked, this, &GraphPage::addCity);
    connect(ui.delcity, &QPushButton::clicked, this, &GraphPage::deleteCity);
    connect(ui.pushButton, &QPushButton::clicked, this, &GraphPage::findTour);
    connect(ui.addedge, &QPushButton::clicked, this, &GraphPage::addEdge);
    connect(ui.fastestButton, &QPushButton::clicked, this, &GraphPage::findFastest);
    connect(ui.shortestButton, &QPushButton::clicked, this, &GraphPage::findShortest);
    connect(ui.deledge, &QPushButton::clicked, this, &GraphPage::deleteEdge);
    connect(ui.undo_Button, &QPushButton::clicked, this, &GraphPage::undo);

    cerr << " here\n";

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        for (auto e : edges) {
            QPointF start = getCityPosition(QString::fromStdString(e.second->source)) + QPointF(50, 50);
            QPointF end = getCityPosition(QString::fromStdString(e.second->destination)) + QPointF(50, 50);

            e.first->setLine(QLineF(start, end));
            double ratio = static_cast<double>(e.second->trafficLoad) / ((graph->getTotalTraffic() + 1));
            qDebug() << "ratio for:"<<e.second->name<<" is: " << ratio;
            QColor color;
            if (ratio < 0.2)
                color = Qt::blue;
            else if (ratio < 0.5)
                color = QColor(255, 165, 0);
            else
                color = Qt::red;

            QPen pen(color, 2, Qt::DashLine);
            e.first->setPen(pen);
        }
    });
    timer->start(100);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    startTimer(100);

    ui.groupBox->setEnabled(false);
    ui.groupBox_2->setEnabled(false);
    ui.graphicsView->setMouseTracking(true);
    ui.graphicsView->viewport()->setMouseTracking(true);
    ui.graphicsView->viewport()->installEventFilter(this);
    cout << "NOW " << Manager::curUser->userName << '\n';
    for (auto id : Manager::curUser->graphsId) {
        cout << '\n' << Manager::curUser->id << ' ' << id << '\n';
        if (Manager::curUser->editGraphCheck(graph->getID())) {
            ui.groupBox->setEnabled(true);
            ui.groupBox_2->setEnabled(true);
            break;
        }
    }
    ui.undo_Button->setIcon(QIcon("D:/Test/undoicon"));
    ui.undo_Button->setIconSize(QSize(48, 48));
}


void GraphPage::displayGraph()
{
    cerr << "\nEntered displayGraph\n";
    cerr << "is null? " << (graph == nullptr) << '\n';
    cerr << "graphName: " << graph->getName() << '\n';
    for (auto c : graph->nodes) {
        addCity(c.first);
    }
    cerr << "\nDone adding nodes\n";
    for (auto e : graph->edges) {
        QPointF start = getCityPosition( QString::fromStdString(e.second->source));
        QPointF end = getCityPosition( QString::fromStdString(e.second->destination));
        QPen pen(Qt::blue, 2, Qt::DashLine);
        animatedLine = scene->addLine(QLineF(start + QPointF(50, 50), end + QPointF(50, 50)), pen);
        animatedLine->setZValue(-1);
        edges.append(make_pair(animatedLine, graph->edges[e.first]));
    }
}









//                         **************************** Modify Graph ****************************

void GraphPage::addCity() {
    if (!scene) return;
    QString cityName = ui.cityname->text();
    if (ui.cityname->text().isEmpty()) {
        QMessageBox::warning(this, "Input Required", "Please fill in the field.");
        return;
    }
    if(!Tools::validateName(cityName.toStdString(), this)) {
        return;
    }
    if(graph->nodeIsFound(cityName.toStdString()))
    {
        QMessageBox::warning(this, "Invalid Input", "This City Already Exists , Please Enter Another Name");
        return;
    }
    graph->addNode(cityName.toStdString());
    QStringList iconPaths = {
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
    int randomIndex = QRandomGenerator::global()->bounded(iconPaths.size());
    QPixmap cityIcon(iconPaths[randomIndex]);
    cityIcon = cityIcon.scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    qreal x = QRandomGenerator::global()->bounded(180, 660);
    qreal y = QRandomGenerator::global()->bounded(10, 350);


    QGraphicsPixmapItem* item = scene->addPixmap(cityIcon);
    item->setPos(QPointF(x, y));
    QGraphicsTextItem* label = scene->addText(cityName);
    label->setPos(x , y -25);

    QFont font("Segoe UI", 12, QFont::Bold);
    font.setItalic(true);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
    label->setFont(font);
    label->setDefaultTextColor(Qt::darkBlue);

    QGraphicsItemGroup* group = scene->createItemGroup({ item, label });
    group->setFlag(QGraphicsItem::ItemIsMovable);

    cityGroups[cityName] = group;
    cityGraphics[cityName.toStdString()]=randomIndex;
    graph->nodes[cityName.toStdString()]->iconId = randomIndex;
    cerr << cityName.toStdString() << '\n';
    if(!isUndo)
    {
        vector<Edge> v;
        for(auto edge:graph->nodes[cityName.toStdString()]->edges)
            v.push_back(Edge( graph->edges[edge]->name,graph->edges[edge]->source,graph->edges[edge]->destination,graph->edges[edge]->length,graph->edges[edge]->directed));

        lastOperations.push({1,cityName.toStdString(),v});
    }
}



void GraphPage::addCity(string cityName) {
    if (!scene) return;
    cerr << "\nadding....\n";
    QStringList iconPaths = {
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
    cerr << "\nAfter Icons\n";
    cerr << "graph size: " << graph->nodes.size() << '\n';
    cerr << "name: " << cityName << ' ' << " is found? " << (graph->nodes.find(cityName) == graph->nodes.end())
         << "\nIcon index: " << graph->nodes[cityName]->iconId << '\n';
    graph->nodes[cityName]->iconId = QRandomGenerator::global()->bounded(iconPaths.size());
    QPixmap cityIcon(iconPaths[graph->nodes[cityName]->iconId]);
    cerr << "after\n";
    cityIcon = cityIcon.scaled(70, 70, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    qreal x = QRandomGenerator::global()->bounded(180, 660);
    qreal y = QRandomGenerator::global()->bounded(10, 350);

    QGraphicsPixmapItem* item = scene->addPixmap(cityIcon);
    item->setPos(QPointF(x, y));
    QGraphicsTextItem* label = scene->addText(QString::fromStdString(cityName));
    label->setPos(x, y - 25);

    QFont font("Segoe UI", 12, QFont::Bold);
    font.setItalic(true);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 2);
    label->setFont(font);
    label->setDefaultTextColor(Qt::darkBlue);

    QGraphicsItemGroup* group = scene->createItemGroup({ item, label });
    group->setFlag(QGraphicsItem::ItemIsMovable);

    cityGroups[QString::fromStdString(cityName)] = group;
}

void GraphPage::addEdge() {
    if(!scene)
        return;

    QString name = ui.lineEdit->text();
    QString from = ui.from->text();
    QString to = ui.to->text();
    int length = ui.len->text().toInt();
    bool directed = ui.directed->isChecked();
    if (name.isEmpty() || from.isEmpty() || to.isEmpty() || ui.len->text().isEmpty()) {
        QMessageBox::warning(this, "Input Required", "All fields must be filled.");
        return;
    }
    if (from == to) {
        QMessageBox::warning(this, "Invalid Input", "Source and destination cities cannot be the same.");
        return;
    }
    if (!graph->nodeIsFound(from.toStdString()) || !graph->nodeIsFound(to.toStdString())) {
        QMessageBox::warning(this, "Invalid City", "One or both cities do not exist in the graph.");
        return;
    }
    if (length <= 0) {
        QMessageBox::warning(this, "Invalid Length", "Length must be a positive integer.");
        return;
    }
    if (graph->edgeIsFound(name.toStdString())) {
        QMessageBox::warning(this, "Duplicate Edge", "An edge with this name already exists.");
        return;
    }
    if(!Tools::validateName(name.toStdString(), this)) {
        return;
    }
    graph->addEdge(name.toStdString(), from.toStdString(), to.toStdString(), length, directed);

    if (!cityGroups.contains(from) || !cityGroups.contains(to)) return;
    QGraphicsItemGroup* fromGroup = cityGroups[from];
    QGraphicsItemGroup* toGroup = cityGroups[to];
    QPointF fromPos = getCityPosition(from);
    QPointF toPos = getCityPosition(to);
    if (fromPos == QPointF(-1, -1) || toPos == QPointF(-1, -1)) {
        QMessageBox::warning(this, "Invalid City", "From or To city doesn't exist.");
        return;
    }
    drawAnimatedLine(fromPos, toPos, name, from, to);
    qDebug() << getCityPosition(from).x();
    auto edge= graph->edges[name.toStdString()];
    vector<Edge>v;
    v.push_back(Edge( edge->name,edge->source,edge->destination,edge->length,edge->directed));

    if(!isUndo)
        lastOperations.push({2, "", v});
}

void GraphPage::deleteCity() {
    inOperation = 1;
    fromDeleteCity=true;
    QString cityName = ui.cityname->text();
    if (!graph->nodeIsFound(cityName.toStdString())) {
        QMessageBox::warning(this, "Invalid Input", "Please Enter a Valid City Name");
        return;
    }
    Node* node = graph->getNode(cityName.toStdString());
    unordered_set<string>edgeNames = node->edges;
    if(!isUndo)
    {
        vector<Edge> v;

        cerr<<cityName.toStdString();
        cerr<<"Noooooooooooo";
        cerr<<graph->nodes[cityName.toStdString()]->edges.size();
        for(auto edge:graph->nodes[cityName.toStdString()]->edges)
            v.push_back(Edge( graph->edges[edge]->name,graph->edges[edge]->source,graph->edges[edge]->destination,graph->edges[edge]->length,graph->edges[edge]->directed));
        lastOperations.push({3,cityName.toStdString(),v});
    }
    for (auto edg : edgeNames) {
        ui.lineEdit->setText(QString::fromStdString(edg));
        deleteEdge();
    }


    for (QGraphicsItem* item : scene->items()) {
        QGraphicsItemGroup* group = qgraphicsitem_cast<QGraphicsItemGroup*>(item);
        if (group && group->childItems().size() >= 2) {
            QGraphicsTextItem* label = qgraphicsitem_cast<QGraphicsTextItem*>(group->childItems().at(1));
            if (label && label->toPlainText() == cityName) {
                scene->removeItem(group);
                delete group;
                break;
            }
        }
    }
    inOperation = 0;
    fromDeleteCity = false;
    graph->deleteNode(cityName.toStdString());
}

void GraphPage::deleteEdge() {
    string edgeName = ui.lineEdit->text().toStdString();
    if (!graph->edgeIsFound(edgeName)) {
        QMessageBox::warning(this, "Invalid Input", "Please Enter a Valid Edge Name");
        return;
    }
    // cerr << "\nStarted Deleting edge.....\n";
    // cout << "Is it? " << graph->bridgeBFS(graph->edges[edgeName]->source, edgeName) << '\n';
    // graph->tarjan(graph->edges[edgeName]->source, "");
    int bridge = 1;
    auto edge = graph->edges[edgeName];
    vector<Edge>v;
    v.push_back(Edge( graph->edges[edgeName]->name,graph->edges[edgeName]->source,graph->edges[edgeName]->destination,graph->edges[edgeName]->length,graph->edges[edgeName]->directed));

    string src = edge->source, dest = edge->destination;
    if(!edge->directed) {
        bridge = 2;
        graph->bridgeBFS(dest, bridge, edgeName);
    }
    //  cerr << "\nMiddle\n";
    graph->bridgeBFS(src, bridge, edgeName);
    if(bridge && inOperation == 1) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Note", "Your graph would be disconnected, do you want to proceed?", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::No)
            return;
        --inOperation;
    }
    // cerr << "\nBefore\n";
    for (int i = 0; i < edges.size(); ++i) {
        if (edges[i].second->name == edgeName) {
            scene->removeItem(edges[i].first);
            delete edges[i].first;
            edges.removeAt(i);
            break;
        }
    }
    // cerr << "\nAfter\n";
    if(!isUndo&&!fromDeleteCity)
        lastOperations.push({4, "",v});
    graph->deleteEdge(edgeName);

    // cerr << "Last\n";
}











//                         **************************** Graph Requests ****************************

void GraphPage::findTour() {

    std::vector<std::string> tour = graph->DFS(ui.lineEdit_2->text().toStdString());
    if (tour.empty()) {
        QMessageBox::information(this, "No Tour", "Could not find a tour from the selected city.");
        return;
    }
    QString tourStr="";
    for (size_t i = 0; i < tour.size(); ++i) {
        tourStr += QString::fromStdString(tour[i]);
        if (i != tour.size() - 1) tourStr += " -> ";
    }
    Manager::getInstance()->curUser->recentSearch.push({"Find Tour","City : "+ui.lineEdit_2->text().toStdString()});
    QMessageBox::information(this, "Exploration Tour", "🧭 Longest Tour:\n" + tourStr);
    PathPage* pathPage = new PathPage(this,  tour, graph->getName());
    pathPage->show();
}


void GraphPage::findFastest()
{
    Model::PathFinder getPath;

    string start = ui.startCity->text().toStdString(), end = ui.endCity->text().toStdString();
    if(start.empty() || end.empty() || !graph->nodeIsFound(start) || !graph->nodeIsFound(end)) {
        QMessageBox::information(this, "Invalid Input", " Please Enter Existing Nodes!!" );
        return;
    }
    Path path = getPath.findPath(start, end, graph->nodes, graph->edges, 0);
    ui.distance->setPlainText(QString::number(path.totalCost) + " Kilometers");
    ui.time->setPlainText(QString::number(path.totalTime) + " second");
    QString pathStr = "";
    for (int i = 0; i < path.Path_Nodes.size();i++) {

        pathStr += QString::fromStdString(path.Path_Nodes[i]);
        if(i != path.Path_Nodes.size()-1)
            pathStr += " -> ";
    }
    Manager::getInstance()->curUser->recentSearch.push({"Fastest Path","{ start : " + start + " , end: " + end + " }"});
    QMessageBox::information(this, "Fastest Path", " Fastest Path:\n" + pathStr);
}

void GraphPage::undo()
{    if (lastOperations.empty())
        return;
    int op;
    string lastNode;
    vector<Edge> lastEdges;
    tie(op, lastNode, lastEdges) = lastOperations.top();
    cerr<<op;
    lastOperations.pop();
    isUndo = true;
    if (op == 1) { // addnode
        ui.cityname->setText(QString::fromStdString(lastNode));
        deleteCity();
    }
    else if (op == 2) { // addedge
        ui.lineEdit->setText(QString ::fromStdString(lastEdges.back().name));
        deleteEdge();
    }
    else if (op == 3) { // deletenode
        ui.cityname->setText(QString::fromStdString(lastNode));
        addCity();
        cerr<<lastEdges.size();
        for (auto edge : lastEdges) {
            cerr<<edge.name;
            ui.lineEdit->setText(QString::fromStdString(edge.name));
            cerr<<edge.source;
            ui.from->setText(QString::fromStdString(edge.source));
            cerr<<edge.destination;
            ui.to->setText(QString::fromStdString(edge.destination));
            cerr<<edge.length;

            string s=to_string(edge.length);
            ui.len->setText(QString::number(edge.length));
            cerr<<edge.directed;

            ui.directed->setChecked(edge.directed);

            cerr<<"addedge start";
            addEdge();
        }
        cerr<<"doneundo";
    }
    else { // deleteedge
        auto edge = lastEdges[0];
        ui.lineEdit->setText(QString::fromStdString(edge.name));
        ui.from->setText(QString::fromStdString(edge.source));
        ui.to->setText(QString::fromStdString(edge.destination));
        string s=to_string(edge.length);
        ui.len->setText(QString::number(edge.length));
        ui.directed->setChecked(edge.directed);

        addEdge();
    }
    isUndo = false;

}
void GraphPage::findShortest()
{
    Model::PathFinder getPath;
    string start = ui.startCity->text().toStdString(), end = ui.endCity->text().toStdString();
    if(start.empty() || end.empty() || !graph->nodeIsFound(start) || !graph->nodeIsFound(end)) {
        QMessageBox::information(this, "Invalid Input", " Please Enter Existing Nodes!!" );
        return;
    }
    Path path = getPath.findPath(start, end, graph->nodes, graph->edges, 1);
    ui.distance->setPlainText(QString::number(path.totalCost) + " Kilometers");
    ui.time->setPlainText(QString::number(path.totalTime)+ " second");
    QString pathStr = "";

    for (int i = 0; i < path.Path_Nodes.size();i++) {

        pathStr += QString::fromStdString(path.Path_Nodes[i]);
        if(i != path.Path_Nodes.size()-1)
            pathStr += " -> ";
    }
    Manager::getInstance()->curUser->recentSearch.push({"Shortest Path",start + "--->" + end});
    QMessageBox::information(this, "Shortest Path", " Shortest Path:\n" + pathStr);

}









//                         **************************** Our Helper Functions ****************************

QPointF GraphPage::getCityPosition(const QString& cityName) {
    for (QGraphicsItem* item : scene->items()) {
        QGraphicsTextItem* label = qgraphicsitem_cast<QGraphicsTextItem*>(item);
        if (label && label->toPlainText() == cityName) {
            return label->scenePos();
        }
    }
    return QPointF(-1, -1);
}

bool GraphPage::eventFilter(QObject* obj, QEvent* event) {
    if (obj == ui.graphicsView->viewport() && event->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        QPointF scenePos2 = ui.graphicsView->mapToScene(mouseEvent->pos());
        QString posText = QString("X: %1, Y: %2")
                              .arg(scenePos2.x(), 0, 'f', 2)
                              .arg(scenePos2.y(), 0, 'f', 2);
        for (auto e : edges) {
            if (e.first->contains(scenePos2)) {
                QToolTip::showText(mouseEvent->globalPosition().toPoint(), QString::fromStdString(e.second->to_string()));

            }


        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void GraphPage::drawAnimatedLine(const QPointF& start, const QPointF& end, QString name, QString from, QString to)
{
    animatedLine = scene->addLine(QLineF(start + QPointF(50, 50), start + QPointF(50, 50)), QPen(Qt::blue, 2, Qt::DashLine));
    animatedLine->setZValue(-1);
    QObject* proxy = new QObject(this);

    QPropertyAnimation* animation = new QPropertyAnimation(proxy, "pos");
    animation->setDuration(800);
    animation->setStartValue(start + QPointF(50, 50));
    animation->setEndValue(end+ QPointF(50, 50));
    //animation->valueChanged();
    connect(animation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        QPointF currentEnd = value.toPointF();
        animatedLine->setLine(QLineF(start + QPointF(50, 50), currentEnd));
    });

    animation->start();
    edges.append(make_pair(animatedLine, graph->edges[name.toStdString()]));
}









//                         **************************** Buttons ****************************
void GraphPage::on_pushButton_8_clicked()
{
    History *h=new History(Manager::getInstance()->curUser,this);
    h->show();
}


void GraphPage::on_startTraverse_clicked()
{
    // vector<BfsNode*>v=graph->BFS(ui.lineEdit_4->text().toStdString());
    // for(auto& bNode:v)
    // {
    //     for(auto city:cityGraphics)
    //         if(bNode->name==city.first.toStdString())
    //         {bNode->indx=city.second;
    //             qDebug()<<bNode->name<<" "<<bNode->indx;
    //         }
    // }
}

void GraphPage::on_traverseNode_clicked() {
    string traverseNode = ui.findCitiesInput->text().toStdString();
    if(!graph->nodeIsFound(traverseNode)) {
        QMessageBox::critical(this,"Error", "Enter an existing city name!");
        return;
    }
    Manager::getInstance()->curUser->recentSearch.push({"Traverse", "City : " + traverseNode});
    Traverse *t = new Traverse(graph, cityGraphics, traverseNode, this);
    t->show();
}
void GraphPage::on_find_Bridge_clicked() {
    if(graph->edges.empty()) {
        QMessageBox::warning(this, "Error", "NO EDGES FOUND");
    }
    QVector<string> bridges;
    string s = "";
    for(auto edge : graph->edges) {
        int bridge = 1;
        string src = edge.second->source, dest = edge.second->destination;
        if(!edge.second->directed) {
            bridge = 2;
            graph->bridgeBFS(dest, bridge, edge.first);
        }
        graph->bridgeBFS(src, bridge, edge.first);
        if(bridge) {
            s += edge.first + ", ";
        }
    }
    while(s.back() == ' ' || s.back() == ',')
        s.pop_back();
    QMessageBox::warning(this, "Bridges Found", QString::fromStdString(s));
}
GraphPage::~GraphPage()
{}
