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


//vector<string> Graph::BFS(string name) {
//	//Route({child, front.second}) = front.first
//	//q(child, parent)
//	queue<pair<string, string>> q;
//	unordered_map<string, bool> visited;
//
//	pair <string, string> ans;
//	vector<string> result;
//
//	// Node* node = getNode(name);
//	q.push({nullptr, name});
//	visited[name] = true;
//	while (!q.empty()) {
//		pair front = q.front();
//		q.pop();
//		if (front.second == name) {
//			ans = front;
//			break;
//		}
//
//		for (auto child : cities[name]->neighbours) {
//			if (visited[child] == 1) continue;
//			visited[child] = true;
//			q.push({front.second, child});
//			Route[{child, front.second}] = front.first;
//		}
//	}
//
//	//make the path
//	while (ans.second != nullptr) {
//		int previous_node = Route[{ans.second, ans.first}];
//		ans = {ans.first, previous_node};
//		result.push_back(previous_node);
//	}
//
//	return result;
//}
