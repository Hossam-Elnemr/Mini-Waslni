# include "Manager.h"
# include <string>
# include <iostream>
using namespace std;
Graph* Manager::getGraph(std::string name) {
	Graph* g = new Graph(name);
	return g;
}
