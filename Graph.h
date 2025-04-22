#pragma once

# include "Path.h"
# include "Node.h"
# include "Edge.h"
# include <vector>
# include <unordered_map>
# include <map>
# include <vector>
using namespace std;
class Graph {
	int id;
	Node* getNode(string name);
	Edge* getEdge(string name);
	static int numberOfGraphs;
	bool validate();
public:
	unordered_map<string, Node*> cities;
	unordered_map<string, Edge*> roads;

	string name;
	Graph(string name);
	void addCity(string name);
	void addEdge(string name, string src, string dest, int length, bool directed);
	pair<Path, double> shortestPath(string source, string destination);
	pair<Path, double> fastestPath(string source, string destination);
	vector<string> DFS(string name);
	vector<string> BFS(string name);
	int getID();
	void test();
};
