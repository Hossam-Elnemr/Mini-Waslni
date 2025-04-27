// #include "Globals.h"
# include<iostream>
# include<string>
# include<set>
# include<unordered_map>
using namespace std;
class Node {
public:
	string name;
	int id, graphId;
	Node(std::string name);
	~Node();
	set<string> neighbours;
	//vector<Edge*> edges;
	void addNeighbour(string name) ;
	string to_string() const noexcept;
	static int numberOfNodes;
};
