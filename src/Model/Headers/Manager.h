# include "Graph.h"
# include <string>
# include <iostream>
# include <vector>
using namespace std;
class Manager {
	static Manager* instance;
	Manager();
public:
	Graph* getGraph(std::string name);
	vector<Graph*> graphs;
	static int graphsCounter;
	int totalCities();
	static Manager* getInstance() {
		if (instance == nullptr)
			instance = new Manager();
		return instance;
	}
};
