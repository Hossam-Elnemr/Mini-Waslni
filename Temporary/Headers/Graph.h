# include "Path.h"
class Graph {
	int id;

	Node* getNode(string name);
	Edge* getEdge(string name);

	bool nodeIsFound(std::string);
	bool edgeIsFound(std::string);
public:
	string name;
	static int numberOfGraphs;
	double totalTraffic;
	map<string, Node*> nodes;
	map<string, Edge*> edges;

	Graph(string name);

	//								  Modify graph
	void addNode(string name);
	void addEdge(string name, string src, string dest, int length, bool directed);
	void deleteNode(string name);
	void deleteEdge(string name);

	//									Traverse
	pair<Path, double> shortestPath(string source, string destination);
	pair<Path, double> fastestPath(string source, string destination);
	vector<string> DFS(string name);
	vector<string> DFS(string name, unordered_map<string, bool>& visited, vector<string>& cities);
	vector<string> BFS(string name);

	//							Getters-Setters & Testing
	int getID();
	double getTotalTraffic();
	static void test();
	string to_string();

	//							Operators
	Node* & operator [](string name) {
		return nodes[name];
	}
};
