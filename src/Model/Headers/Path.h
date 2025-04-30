# include "Edge.h"
class Path {
public:
	Path() : totalCost(-1.0) {}
	vector<string> Path_Edges;
	vector<string> Path_Nodes; 
	double totalCost;
};