#pragma once
# include "Node.h"
class Edge {
public:
	string name, source, destination;;
    static double constant;
	int id, graphId;
    double length, trafficLoad, trafficLength;
	static int numberofEdges;
	bool directed;
	Edge(string name, string src, string dest, int length, bool directed);
    Edge(string name, string src, string dest, int length, bool directed, int id, int graphId, double trafficLoad);
	~Edge();
	void setGraphid(int graphId);
	double trafficCost(double sum);
    double lengthCost();
    double getTime(double d);
    string to_string() const;
};
