#pragma once
# include "Path.h"
# include "bfsnode.h"
# include "QMessageBox.h"
class Graph {
	int id;
	string name;

    bool isUndo = false; // says if that operation came from undo or not
    //stack <tuple<int, string, vector<Edge>>> lastOperations;
public:
	Graph(string name);
    Graph(int id, string name , bool root , int ndfn, const vector<vector<string>>& nodes, const vector<vector<string>>& edges); // to load graph data from file
	static int numberOfGraphs;
    stack <tuple<int, string, vector<Edge>>> lastOperations;

    unordered_map<string, Node*> nodes;
    unordered_map<string, Edge*> edges;
    unordered_map<string, vector<pair<double, string>>> adj; // {u, {w, v}}

    //                              Tarjan
    unordered_map <string, int> dfn, LowLink;
    unordered_map<string, bool> bridge, artPoint;
    bool root;
    int ndfn;

    //								  Modify graph
	void addNode(string name); // 1
	void addEdge(string name, string src, string dest, int length, bool directed); // 2
	void deleteNode(string name); // 3
	void deleteEdge(string name); // 4
	void undo();
    bool nodeIsFound(std::string);
    bool edgeIsFound(std::string);

	//									Traverse
    void DFS(string current, unordered_map<string, bool>& visited,vector<string>& currentPath, vector<string>& longestPath);
    vector<string> DFS(string name);
    vector<BfsNode*> BFS(string name);
    bool bridgeBFS(string name, int &warning, string Removed = "");
    void tarjan(string node, string parent = "");

	//							Getters-Setters & Testing
	int getID();
	string getName();
	string toString();
	double getTotalTraffic();
    Node* getNode(string name);
    Edge* getEdge(string name);

    static void test();
    // void testMe();
};
