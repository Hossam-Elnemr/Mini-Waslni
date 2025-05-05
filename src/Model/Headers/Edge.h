# include "Node.h"
class Edge {
public:
	string name, source, destination;;
	int id, graphId;
	double length, trafficLoad;
	static int numberofEdges;
	bool directed;
	Edge(string name, string src, string dest, int length, bool directed);
	~Edge();
	void setGraphid(int graphId);
	double trafficCost(double sum);
	double lengthCost();
	string to_string() const;
};