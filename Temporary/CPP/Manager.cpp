# include "../Headers/Manager.h"

int Manager::graphsCounter = 0;
Manager* Manager::instance = nullptr;

Manager::Manager() {
	
}

Graph* Manager::getGraph(std::string name) {
	Graph* g = new Graph(name);
	graphs.push_back(g);
	++graphsCounter;
	return g;
}

int Manager::totalCities() {
	int sum = 0;
	for (auto graph : graphs)
		sum += (int)graph->nodes.size();
	return sum;
}