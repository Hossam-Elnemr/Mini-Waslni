# include "Graph.h"
int Graph::numberOfGraphs = 0;

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
	roads[name] = newRoad;

	std::cout << src << " -> " << dest << '\n';

	source->addNeighbour(name);
	if (!directed) {
		destination->addNeighbour(name);
		std::cout << dest << " -> " << src << '\n';;
	}
}
Node* Graph::getNode(string name) {
	return cities[name];
}
Edge* Graph::getEdge(string name) {
	return roads[name];
}

int Graph::getID() {
	return id;
}

vector<string> Graph::BFS(string name) {
	queue<string> q;
	unordered_map<string, bool> visited;

	vector<string> result;
	q.push(name);
	visited[name] = true;
	string city;
	while (!q.empty()) {
		string next_city = q.front();
		q.pop();
		result.push_back(next_city);
		for (auto edge : cities[next_city]->neighbours) {
			if (next_city == roads[edge]->source->name)
				city = roads[edge]->destination->name;
			else if (!roads[edge]->directed)
				city = roads[edge]->source->name;
			else continue;

			if (visited[city] == 1) continue;
			visited[city] = 1;
			q.push(city);
		}
	}
	return result;
}

void Graph::test() {
	Graph* g = new Graph("graph1");
	//Graph* g2 = m.getGraph("graph2");
	g->addCity("Cairo");
	g->addCity("Giza");
	g->addCity("Alex");
	g->addCity("Aswan");
	g->addCity("Matrouh");
	g->addEdge("First edge", "Cairo", "Giza", 4, false);
	g->addEdge("second edge", "Cairo", "Alex", 4, false);
	g->addEdge("fourth edge", "Matrouh", "Cairo", 4, true);
	g->addEdge("third edge", "Alex", "Aswan", 4, false);
	//cout << g->roads["First edge"]->graphId;

	vector <string> v;
	string start = "Matrouh";
	v = g->BFS(start);
	std::cout << "\n\nFirst Test:\nSource is " << start << '\n';
	for (int i = 0; i < v.size(); i++) {
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

	cout << "Cities: " << g->cities.size() << ", Roads: " << g->roads.size() << "\n\n";
}