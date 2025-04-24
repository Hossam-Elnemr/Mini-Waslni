#ifndef GRAPH_MANAGER_CONTROLLER_H
#define GRAPH_MANAGER_CONTROLLER_H

#include "../Model/Headers/Globals.h"
#include "../Model/Headers/GraphManager.h"
#include "../Model/Headers/CitiesMapperID.h"
#include "../Model/Headers/PathFinder.h"


#include "../View/GraphManagerView.h"
#include "../Model/Headers/Database.h"

namespace Controller {
	//This class To handle the graph operations.
	class GraphManagerController {
		Model::GraphManager* graphManager;
		View::GraphManagerView* graphManagerView;

	public:
		GraphManagerController();
		
		//Validation Functions and Error Handling and to interact with logic and view :)
		void addGraph();
		void addCity();
		void addEdge();
		void removeGraph();
		void removeCity();
		void pathFinding();

		~GraphManagerController();
	};
}

#endif