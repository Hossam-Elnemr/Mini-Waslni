# include "Graph.h"
int Graph::numberOfGraphs = 0;
using namespace std;

Graph::Graph(string name) {
	this->name = name;
	id = numberOfGraphs++;
}

//								Validations

bool Graph::nodeIsFound(std::string name) {
	return nodes.find(name) != nodes.end();
}
bool Graph::edgeIsFound(std::string name) {
	return edges.find(name) != edges.end();
}



//								  Modify
void Graph::addNode(string name) {
	if (nodeIsFound(name))
		return std::cout << "node Name is found!\nEnter another name\n", void();

	Node* newnode = new Node(name);
	nodes[newnode->name] = newnode;
}

void Graph::addEdge(string name, string src, string dest, int length, bool directed) {
	if (!nodeIsFound(src) || !nodeIsFound(dest) || edgeIsFound(name))
		return std::cout << "Error!!\nEnter a new edge name between two existing nodes!\n", void();


	Node* source = getNode(src);
	Node* destination = getNode(dest);
	Edge* newRoad = new Edge(source, destination, name, length, directed);

	newRoad->setGraphid(id);
	edges[name] = newRoad;

	std::cout << src << " -> " << dest << '\n';

	source->addNeighbour(name);
	if (!directed) {
		destination->addNeighbour(name);
		std::cout << dest << " -> " << src << '\n';
	}
}

void Graph::deleteNode(string name) {
	if (!nodeIsFound(name))
		return cout << "node not found!\n", void();
	map<string, Edge*> temp = edges;
	Node* deletednode = getNode(name);
	for (auto var : temp) {
		string edgeName = var.first;
		auto edge = var.second;
		Node* src = getNode(edge->source->name), *dest = getNode(edge->destination->name);

		if (name == src->name || name == dest->name)
			deleteEdge(edgeName);
	}

	delete deletednode;
	nodes.erase(name);
}

void Graph::deleteEdge(string name) {
	if (!edgeIsFound(name))
		return cout << "Road not found!\n", void();

	auto edge = edges[name]; // object
	Node* src = getNode(edge->source->name), *dest = getNode(edge->destination->name);
	bool directed = edge->directed;
	src->neighbours.erase(name);
	if(!directed)
		dest->neighbours.erase(name);

	delete edge;
	edges.erase(name);
}



//								Traverse
vector<string> Graph::BFS(string name) {
	if (!nodeIsFound(name))
		return std::cout << "node not found!\nEnter a valid node.\n", vector<string>();


	queue<string> q;
	unordered_map<string, bool> visited;

	vector<string> result;
	q.push(name);
	visited[name] = true;
	string node;
	while(!q.empty()) {
		string next_node = q.front();
		q.pop();
		result.push_back(next_node);
		for (auto edge : nodes[next_node]->neighbours) {
			if (next_node == edges[edge]->source->name)
				node = edges[edge]->destination->name;
			else if (!edges[edge]->directed)
				node = edges[edge]->source->name;
			else continue;

			if (visited[node] == 1) continue;
			visited[node] = 1;
			q.push(node);
		}
	}
	return result;
}




Node* Graph::getNode(string name) {
	return nodes[name];
}
Edge* Graph::getEdge(string name) {
	return edges[name];
}

int Graph::getID() {
	return id;
}

string Graph::to_string() {
	string res = "";
	for (auto var : nodes) {
		auto node = var.second;
		res += node->to_string() + "\n\n";
	}
	return res;
}











void Graph::test() {
	Graph* g = new Graph("graph1");
	//Graph* g2 = new Graph("graph2");
	g->addNode("Cairo");
	g->addNode("Giza");
	g->addNode("Alex");
	g->addNode("Aswan");
	g->addNode("Matrouh");
	g->addEdge("First edge", "Cairo", "Giza", 4, false);
	g->addEdge("second edge", "Cairo", "Alex", 4, false);
	g->addEdge("fourth edge", "Matrouh", "Cairo", 4, true);
	g->addEdge("third edge", "Alex", "Aswan", 4, false);
	cout << '\n';
	cout << g->to_string();

	g->deleteNode("Cairo");

	cout << "########\n\n";
	cout << g->to_string();
	
	vector <string> v;
	string start = "Matrouh";
	v = g->BFS(start);
	std::cout << "\n\nFirst Test:\nSource is " << start << '\n';
	for(int i = 0; i < v.size(); i++) {
		cout << v[i];
		if (i != v.size() - 1)
			cout << " -> ";
	}

	cout << "\n\n";
	start = "Cairo";
	std::cout << "Second Test:\nSource is " << start << '\n';
	v = g->BFS(start);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i];
		if (i != v.size() - 1)
			cout << " -> ";
	}
	cout << "\n\n";

	cout << "nodes: " << g->nodes.size() << ", edges: " << g->edges.size() << "\n\n";

}
