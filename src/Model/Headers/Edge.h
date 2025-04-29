#ifndef EDGE_H
#define EDGE_H
# include<iostream>
# include "Node.h"
# include<string>
class Edge {
public:
	std::string name, source, destination;
	int id, graphId;
	double length, trafficLoad;
	static int numberofEdges;
	bool directed;
	Edge(string name, string src, string dest, int length, bool directed);
	~Edge();
	void setGraphid(int graphId);
	double trafficCost();
	double lengthCost();
};
#endif
