#include "GraphManagerController.h"

Controller::GraphManagerController::GraphManagerController()
{
	this->graphManager = new Model::GraphManager();
	this->graphManagerView = new View::GraphManagerView();
	cout << "GraphManagerController Constructor" << endl;
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
	vector<string> path;
	double distance;

	tie(path, distance) = pathFinder.findPath();

	if (distance == -1) { // path not found
	}
	else {
		View::PathPrinter pathPrinter;
		pathPrinter.printPath(path, distance);
	}
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
