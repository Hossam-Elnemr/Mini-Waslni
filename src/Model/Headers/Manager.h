#ifndef MANAGER_H
#define MANAGER_H
# include "Graph.h"
using namespace std;
class Manager {
	static Manager instance;
	Manager();
public:
	Graph* getGraph(std::string name);
	vector<Graph*> graphs;
	static int graphsCounter;
	int totalCities();
	static Manager getInstance() {
		static Manager instance;
		return instance;
	}
};
#endif