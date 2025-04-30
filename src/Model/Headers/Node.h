# include "Globals.h"
# include "../Helpers/Tools.h"
class Node {
public:
	string name;
	int id, graphId;
	Node(std::string name);
	~Node();
	unordered_set<string> edges;
	void addNeighbour(string name);
	string to_string();
	static int numberOfNodes;
};