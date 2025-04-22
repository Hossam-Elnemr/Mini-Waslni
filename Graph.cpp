# include "Graph.h"

#include <string>
#include <vector>
# include <queue>
# include <stack>
#include <unordered_map>
# include "Node.h"

//#include "../Headers/Node.h"

class Node;
using namespace std;
Graph::Graph(string name) {
	this->name = name;
	id = numberOfGraphs++;
}
void Graph::addCity(string name) {
	if (cities.find(name) != cities.end()) {
		std::cout << "City Name is found!\nEnter another name\n";
		return;
	}
	Node* newCity = new Node(name);
	cities[newCity->name] = newCity;
}

bool Graph::validate() {
	return true;
}


void Graph::addEdge(string name, string src, string dest, int length, bool directed) {
	//validate()
	Node* source = getNode(src);
	Node* destination = getNode(dest);
	Edge* newRoad = new Edge(source, destination, name, length, directed);
	newRoad->setGraphid(id);
	;	roads[name] = newRoad;
	source->addNeighbour(name);
	if (!directed)
		destination->addNeighbour(name);
	id = numberOfGraphs++;
}
Node* Graph::getNode(string name) {
	return cities[name];
}
Edge* Graph::getEdge(string name) {
	return roads[name];
}
void Graph::test() {
	std::cout << numberOfGraphs << ' ' << cities["Cairo"]->numberOfNodes;
}
int Graph::getID() {
	return id;
}
int Graph::numberOfGraphs = 0;


vector<string> Graph::BFS(string name) {
	queue<string> q;
	unordered_map<string, bool> visited;

	vector<string> result;
	q.push(name);
	visited[name] = true;
	while (!q.empty()) {
		string front = q.front();
		q.pop();
		result.push_back(front);

		for (auto child : cities[name]->neighbours) {
			if (visited[child] == 1) continue;
			visited[child] = 1;
			q.push(child);
		}
	}
	return result;
}

