#ifndef MANAGER_H
#define MANAGER_H
# include "Graph.h"
#include "User.h"
# include <string>
# include <iostream>
using namespace std;
class Manager {
	static Manager instance;
	Manager();
public:
	vector<Graph*> graphs;
	unordered_map<string,string> users;
	static int graphsCounter;
	int totalCities();
	static Manager getInstance() {
		static Manager instance;
		return instance;
	}
};
#endif
