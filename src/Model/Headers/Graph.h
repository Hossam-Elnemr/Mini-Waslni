# include <vector>
# include <unordered_map>
# include "Path.h"
# include <queue>
using namespace std;
class Graph {
	Node* getNode(string name);
	Edge* getEdge(string name);
	bool cityIsFound(std::string);
	bool EdgeIsFound(std::string);
	int id;
public:
	Graph(string name);
	static int numberOfGraphs;
	string name;
	double totalTraffic;

	unordered_map<string, Node*> cities;
	unordered_map<string, Edge*> roads;

	//								  Modify graph
	void addCity(string name);
	void addEdge(string name, string src, string dest, int length, bool directed);

	//									Traverse
	pair<Path, double> shortestPath(string source, string destination);
	pair<Path, double> fastestPath(string source, string destination);
	vector<string> DFS(string name);
	vector<string> BFS(string name);

	//							Getters-Setters & Testing
	int getID();
	static void test();


	//							Operators
	Node* & operator [](string name) {
		return cities[name];
	}
};
