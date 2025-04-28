# include "Globals.h"
class Node {
public:
	string name;
	int id, graphId;
	Node(std::string name);
	~Node();
	set<string> neighbours;
	//vector<Edge*> edges;
	void addNeighbour(string name);
	string to_string();
	static int numberOfNodes;
};