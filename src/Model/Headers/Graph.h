#ifndef GRAPH_H
#define GRAPH_H
#include<string>
#include "Node.h"
#include "Edge.h"
# include <vector>
# include <unordered_map>
# include <map>
# include "Path.h"
# include <queue>
#include <stack>

using namespace std;
class Graph {
	Node* getNode(string name);
	Edge* getEdge(string name);

	bool nodeIsFound(std::string);
	bool edgeIsFound(std::string);
	int id;
	bool cur_undo=false;
	stack <tuple<int, string, vector<Edge>>> lastOperations;
public:
	Graph(string name);
	static int numberOfGraphs;
	string name;
	double totalTraffic;

	unordered_map<string, Node*> nodes;
	unordered_map<string, Edge*> edges;

	//								  Modify graph
	void addNode(string name);
	void addEdge(string name, string src, string dest, int length, bool directed);
	void deleteNode(string name);
	void deleteEdge(string name);
	void undo();

	//									Traverse
	Path shortestPath(string source, string destination);
	Path fastestPath(string src, string dest);
	vector<string> DFS(string name);
	vector<string> BFS(string name);

	//							Getters-Setters & Testing
	int getID();
	static void test();
	string to_string();

	//							Operators
	Node*& operator [](string name) {
		return nodes[name];
	}
};
#endif
