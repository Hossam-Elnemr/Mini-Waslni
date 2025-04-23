#pragma once
# include "Graph.h"
# include <string>
# include <iostream>
using namespace std;
class Manager {
public:
	Graph* getGraph(std::string name);
};
