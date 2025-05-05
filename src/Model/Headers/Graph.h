# include "Path.h"
class Graph {
	int id;
	string name;
	bool nodeIsFound(std::string);
	bool edgeIsFound(std::string);

	Node* getNode(string name);
	Edge* getEdge(string name);

	bool isUndo = false; // variable that says if that operation came from undo or not
	stack <tuple<int, string, vector<Edge>>> lastOperations;
public:
	Graph(string name);
	Graph(int id, string name, const vector<vector<string>>& nodes, const vector<vector<string>>& edges); // to load graph data from file
	static int numberOfGraphs;

	unordered_map<string, Node*> nodes;
	unordered_map<string, Edge*> edges;

	//								  Modify graph
	void addNode(string name); // 1
	void addEdge(string name, string src, string dest, int length, bool directed); // 2
	void deleteNode(string name); // 3
	void deleteEdge(string name); // 4
	void undo();

	//									Traverse
	pair<Path, double> shortestPath(string source, string destination);
	Path fastestPath(string source, string destination);
	vector<string> DFS(string name, unordered_map<string, bool>& visited, vector<string>& cities);
	vector<string> DFS(string name);
	vector<string> BFS(string name);

	//							Getters-Setters & Testing
	int getID();
	string getName();
	string toString();
	double getTotalTraffic();

	static void test();
};