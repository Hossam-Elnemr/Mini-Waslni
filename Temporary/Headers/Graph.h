# include "Path.h"
class Graph {
	Node* getNode(string name);
	Edge* getEdge(string name);

	bool nodeIsFound(std::string);
	bool edgeIsFound(std::string);
	int id;
public:
	Graph(string name);
	static int numberOfGraphs;
	string name;
	double totalTraffic;

	map<string, Node*> nodes;
	map<string, Edge*> edges;

	//								  Modify graph
	void addNode(string name);
	void addEdge(string name, string src, string dest, int length, bool directed);
	void deleteNode(string name);
	void deleteEdge(string name);

	//									Traverse
	pair<Path, double> shortestPath(string source, string destination);
	pair<Path, double> fastestPath(string source, string destination);
	vector<string> DFS(string name);
	vector<string> BFS(string name);

	//							Getters-Setters & Testing
	int getID();
	static void test();
	string to_string();

	//							Operators
	Node* & operator [](string name) {
		return nodes[name];
	}
};