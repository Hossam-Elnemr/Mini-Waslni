#ifndef GRAPH_MANAGER_CONTROLLER_H
#define GRAPH_MANAGER_CONTROLLER_H

namespace Controller {
	//This class To handle the graph operations.
	class GraphManagerController {
	public:
		GraphManagerController() = default;
		
		//Validation Functions and Error Handling and to interact with logic and view :)
		void addGraph();
		void addCity();
		void addEdge();
		void removeGraph();
		void removeCity();

		~GraphManagerController();
	};
}

#endif