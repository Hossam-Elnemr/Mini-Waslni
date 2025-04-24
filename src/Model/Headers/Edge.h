# include<iostream>
#include "Globals.h"
# include "Node.h"
# include<string>
class Edge {
public:
	Node* source, * destination;
	std::string name;
	int id, graphId;
	double length, trafficLoad;
	static int numberofEdges;
	bool directed;
	Edge(Node* src, Node* dest, std::string name, int length, bool directed);
	~Edge();
	void setGraphid(int graphId);
	double trafficCost();
	double lengthCost();
};
