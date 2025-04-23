#pragma once
#ifndef GRAPH_MANAGER_H
#define GRAPH_MANAGER_H

namespace Model {
	//This class To handle the graph operations.
	class GraphManager {
	public:
		GraphManager() = default;

		void addGraph();
		void addCity();
		void addEdge();
		void removeGraph();
		void removeCity();

		~GraphManager();
	}
}




#endif