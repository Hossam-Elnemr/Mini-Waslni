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
		return std::cout << "Node already exists!", void();
	
	Node* newnode = new Node(name);
	nodes[newnode->name] = newnode;
	if(!cur_undo) lastOperations.push({ 1, name, vector<Edge>() });
}

void Graph::addEdge(string name, string src, string dest, int length, bool directed) {
	if (src == dest || !nodeIsFound(src) || !nodeIsFound(dest) || edgeIsFound(name))
		return std::cout << "Error!!\nEnter a new edge name between two different existing nodes!\n", void();
	if (length<=0) return std::cout << "Enter a positive integer for length.\n", void();
	Edge* newEdge = new Edge(name, src, dest, length, directed);

	newEdge->setGraphid(id);
	edges[name] = newEdge;
	std::cout << src << " -> " << dest << '\n';

	getNode(src)->neighbours[name]=true;
	if (!directed) getNode(dest)->neighbours[name]=true;

	if (!cur_undo) lastOperations.push({ 2, "", vector<Edge>(1, *newEdge) });
}

void Graph::deleteNode(string name) {
	if (!nodeIsFound(name))
		return cout << "node not found!\n", void();

	unordered_map<string, Edge*> temp = edges;
	Node* deletednode = getNode(name);
	vector<Edge> deletededges;

	for (auto var : temp) {
		string edgeName = var.first;
		auto edge = var.second;

		if (name == edge->source || name == edge->destination) {
			deletededges.push_back(*edge);
			deleteEdge(edgeName);
		}
	}
	if (!cur_undo) lastOperations.push({ 3, name, deletededges});
	delete deletednode;
	nodes.erase(name);
}
 
void Graph::deleteEdge(string name) {
	if (!edgeIsFound(name))
		return cout << "Road not found!\n", void();

	auto edge = edges[name]; // object
	Node* src = getNode(edge->source), * dest = getNode(edge->destination);
	bool directed = edge->directed;
	src->neighbours.erase(name);
	if (!directed) dest->neighbours.erase(name);
	if (!cur_undo) lastOperations.push({ 4, "", vector<Edge>(1, *edge) });
	delete edge;
	edges.erase(name);
}

void Graph::undo() {
	if (lastOperations.empty()) {
		//do nothing
		return;
	}
	auto [op, lastNode, lastEdges] = lastOperations.top();
	lastOperations.pop();
	cur_undo = true;
	if (op == 1) {       
		//addnode
		deleteNode(lastNode);
	}
	else if (op == 2) {
		//addedge
		deleteEdge(lastEdges[0].name);
	}
	else if (op == 3) {
		//deletenode
		addNode(lastNode);
		for (auto edge : lastEdges) {
			addEdge(edge.name, edge.source, edge.destination, edge.length, edge.directed);
		}
	}
	else {
		//deleteedge
		auto edge = lastEdges[0];
		addEdge(edge.name, edge.source, edge.destination, edge.length, edge.directed);
	}
	cur_undo = false;
}  

//								Traverse

vector<string> Graph::BFS(string name) {
	if (!nodeIsFound(name))
		return std::cout << "node not found!\nEnter a valid node.\n", vector<string>();

	queue<string> q;
	unordered_map<string, bool> visited;
	vector<string> result;

	string src = name;
	q.push(src);
	visited[name] = true;
	while (!q.empty()) {
		string node = q.front();
		q.pop();
		result.push_back(node);
		for (auto [edge, boole] : nodes[node]->neighbours) {
			string next_node = edges[edge]->destination;
			if (visited[next_node]) continue;
			visited[next_node] = true;
			q.push(next_node);
		}
	}
	return result;
}


Path Graph::fastestPath(string src, string dest) {

	priority_queue<pair<double, string>> pq;
	unordered_map<string, double> mincost;
	unordered_map<string, string> parent;
	Path path;
	pq.push({ 0,src });
	while (!pq.empty()) {
		auto [cost, node] = pq.top();
		pq.pop();
		if (mincost[node] && -cost > mincost[node]) continue;
		for (auto [edge, boole] : nodes[node]->neighbours) {
			string next_node = edges[edge]->destination;
			double cur_cost = -cost + edges[edge]->length;
			if (!mincost[next_node] || cur_cost < mincost[next_node]) {
				pq.push({ -cur_cost, next_node });
				mincost[next_node] = cur_cost;
				parent[next_node] = edge;
			}
		}
	}
	while (parent[dest] != "") {
		path.Path_Edges.push_back(parent[dest]);
		dest = edges[parent[dest]]->source;
	}
	path.total_lengthCost = mincost[dest];
	reverse(path.Path_Edges.begin(), path.Path_Edges.end());
	return path;
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
	cout << "\n\n\n\n";
	cout << g->to_string();
	
	g->addEdge("fi", "Alex", "Matrouh", 4, false);
	cout << "########\n\n\n\n\n";
	cout << g->to_string();
	g->undo();

	cout << "########\n\n\n\n\n";
	cout << g->to_string();
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

	cout << "nodes: " << g->nodes.size() << ", edges: " << g->edges.size() << "\n\n";

	Path p = g->fastestPath("Matrouh", "Aswan");
	for (auto ed : p.Path_Edges) cout << ed << ' ';
}
