#pragma once
#ifndef GRAPH_MANAGER_H
#define GRAPH_MANAGER_H
#include "Globals.h"
#include "Database.h"
#include "CitiesMapperID.h"
namespace Model {
	//This class To handle the graph operations.
	class GraphManager {
		
	public:
		GraphManager();

		void addGraph();
		void addCity(string city);
		void addEdge(string from , string to , int weight, bool isDirected);
		void removeGraph();
		void removeCity();
		void pathFinding();

		~GraphManager();
	};
}

#endif