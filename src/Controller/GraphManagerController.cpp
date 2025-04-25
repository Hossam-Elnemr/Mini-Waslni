#include "GraphManagerController.h"

Controller::GraphManagerController::GraphManagerController()
{
	this->graphManager = new Model::GraphManager();
	this->graphManagerView = new View::GraphManagerView();
	cout << "GraphManagerController Constructor" << endl;
}

void Controller::GraphManagerController::addGraph()
{
	vector<string> cities;
	vector<tuple<string, string, int ,bool>> edges;
	tie(cities, edges) = graphManagerView->getGraphInfo();

	for (const auto &city : cities) {
		graphManager->addCity(city);
	}

	for (const auto& edge : edges) {
		string src, dest;
		int length;
		bool isDirected;
		tie(src, dest, length , isDirected) = edge;
		graphManager->addEdge(src, dest, length , isDirected);
	}
}


void Controller::GraphManagerController::pathFinding()
{
	/*
	* 1- Get the cities names from the view
	* 2- Check if the cities are valid and get the ids
	* 3- Run the dijkstra algorithm in PathFinder Class
	* 4- Construct the path in PathConstructor Class
	* 5- Show the path in PathPrinter Class 
	*/

	string from, to;
	tie(from , to) = graphManagerView->getPathFindingInfo();

	int fromId = Model::CitiesMapperID::getIdByCity(from);
	int toId = Model::CitiesMapperID::getIdByCity(to);

	//validate it
	//.....

	Model::PathFinder pathFinder(fromId, toId);
	/*vector<string> path;
	double distance;*/

	pair<vector<string> , double> ret = pathFinder.findPath();

	if (ret.second == -1) { // path not found
		cout << "Path Not Found\n";
	}
	else {
		View::PathPrinter pathPrinter;
		pathPrinter.printPath(ret.first , ret.second);
	}
}

int Controller::GraphManagerController::showMenu()
{
	vector<string> menu = { "1: Add Graph\n",
		"2: Add City\n",
		"3: Add Edge\n",
		"4: Remove Graph\n",
		"5: Remove City\n",
		"6: Path Finding\n",
		"7: Exit\n" };

	int choice = graphManagerView->showMenu(menu);
	return choice;
}

Controller::GraphManagerController::~GraphManagerController()
{
	if (graphManager != nullptr) {
		delete graphManager;
		graphManager = nullptr;
	}

	if (graphManagerView != nullptr) {
		delete graphManagerView;
		graphManagerView = nullptr;
	}
	cout << "GraphManagerController Destructor" << endl;
}
