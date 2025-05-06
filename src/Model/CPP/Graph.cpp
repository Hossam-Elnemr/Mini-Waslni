# include "../Headers/Graph.h"
int Graph::numberOfGraphs = 0;

Graph::Graph(string name) {
	this->name = name;
	id = numberOfGraphs++;
	//ndfn = 0;
	root = false;
}
Graph::Graph(int id, string name, const vector<vector<string>>& nodes, const vector<vector<string>>& edges) {
	this->id = id;
	this->name = name;
	for (int i = 0; i < (int)nodes.size(); ++i) {
		Node* newNode = new Node(nodes[i][0]);

		for (int j = 1; j < nodes[i].size(); ++j)
			newNode->edges.insert(nodes[i][j]);

		this->nodes[nodes[i][0]] = newNode;
	}

	for (auto& i : edges) {
		Edge* newedge = new Edge(i[0], i[1], i[2], std::stod(i[3]), std::stoi(i[4]));
		this->edges[newedge->name] = newedge;
	}
	numberOfGraphs++;
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
	for (auto s : name)
		if (Tools::isSpecialChar(s))
			return std::cout << "Special characters not allowed!", void();
	if (nodeIsFound(name))
		return std::cout << "node Name is found!\nEnter another name\n", void();

	Node* newnode = new Node(name);
	nodes[newnode->name] = newnode;
	if (!isUndo)
		lastOperations.push({1, name, vector<Edge>()});
}

void Graph::addEdge(string name, string src, string dest, int length, bool directed) {
	for (auto s : name)
		if (Tools::isSpecialChar(s))
			return std::cout << "Special characters not allowed!", void();

	if (src == dest || !nodeIsFound(src) || !nodeIsFound(dest) || edgeIsFound(name))
		return std::cout << "Error!!\nEnter a new edge name between two different existing nodes!\n", void();

	if (length <= 0)
		return std::cout << "Enter a positive integer for length.\n", void();

	Edge* newEdge = new Edge(name, src, dest, length, directed);

	newEdge->setGraphid(id);
	edges[name] = newEdge;

	std::cout << src << " -> " << dest << '\n';

	getNode(src)->edges.insert(name);
	if (!directed) {
		getNode(dest)->edges.insert(name);
		std::cout << dest << " -> " << src << '\n';
	}
	if(!isUndo)
		lastOperations.push({2, "", vector<Edge>(1, *newEdge)});
}

void Graph::deleteNode(string name) {
	if (!nodeIsFound(name))
		return cout << "node not found!\n", void();
	unordered_map<string, Edge*> temp = edges;
	Node* deletednode = getNode(name);
	vector<Edge> deletedEdges;

	for (auto var : temp) {
		string edgeName = var.first;
		auto edge = var.second;

		if (name == edge->source || name == edge->destination) {
			deletedEdges.push_back(*edge);
			deleteEdge(edgeName);
		}
	}

	if (!isUndo)
		lastOperations.push({3, name, deletedEdges});
	delete deletednode;
	nodes.erase(name);
}

void Graph::deleteEdge(string name) {
	if (!edgeIsFound(name))
		return cout << "Road not found!\n", void();

	auto edge = edges[name];
	Node* src = getNode(edge->source), *dest = getNode(edge->destination);
	bool directed = edge->directed;

	src->edges.erase(name);

	if(!directed)
		dest->edges.erase(name);

	if(!isUndo)
		lastOperations.push({4, "", vector<Edge>(1, *edge)});
	delete edge;
	edges.erase(name);
}

void Graph::undo() {
	if (lastOperations.empty()) {
		//do nothing
		return;
	}
	int op;
	string lastNode;
	vector<Edge> lastEdges;
	tie(op, lastNode, lastEdges) = lastOperations.top();

	lastOperations.pop();
	isUndo = true;
	if (op == 1) { // addnode
		deleteNode(lastNode);
	}
	else if (op == 2) { // addedge
		deleteEdge(lastEdges[0].name);
	}
	else if (op == 3) { // deletenode
		addNode(lastNode);
		for (auto edge : lastEdges) {
			addEdge(edge.name, edge.source, edge.destination, edge.length, edge.directed);
		}
	}
	else { // deleteedge
		auto edge = lastEdges[0];
		addEdge(edge.name, edge.source, edge.destination, edge.length, edge.directed);
	}
	isUndo = false;
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
		for (auto edge: nodes[node]->edges) {
			string next_node = edges[edge]->destination;
			if (visited[next_node]) continue;
			visited[next_node] = true;
			q.push(next_node);
		}
	}
	return result;
}

vector<string> Graph::DFS(string name, unordered_map<string, bool>& visited, vector<string>& cities) {
	if (!nodeIsFound(name)) {
		cout << "City not found!\n";
		return cities;
	}

	visited[name] = true;
	cities.push_back(name);
	for (auto edge : nodes[name]->edges) {
		string city;
		if (name == edges[edge]->source)
			city = edges[edge]->destination;
		else
			city = edges[edge]->source;
		if (!visited[city])
			DFS(city, visited, cities);
	}
	return cities;
}
vector<string> Graph::DFS(string start) {
	if (!nodeIsFound(start))
		return cout << "Enter an existing node", vector<string>();
	vector<string> cities;
	unordered_map<string, bool> visited;
	return DFS(start, visited, cities);
}

Path Graph::fastestPath(string src, string dest) {

	priority_queue<pair<double, string>> pq;
	unordered_map<string, double> mincost;
	unordered_map<string, string> parent;
	Path path;
	pq.push({ 0,src });
	while (!pq.empty()) {
		double cost;
		string node;
		tie(cost, node) = pq.top();
		pq.pop();
		if (mincost[node] && -cost > mincost[node]) continue;

		for (auto edge : nodes[node]->edges) {
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
	path.totalCost = mincost[dest];
	reverse(path.Path_Edges.begin(), path.Path_Edges.end());
	return path;
}

double Graph::getTotalTraffic() {
	double result = 0;
	for (const auto &obj : edges)
		result += obj.second->trafficLoad;
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

string Graph::getName() {
	return name;
}


void Graph::test() {
	Graph* g = new Graph("graph1");
	//Graph* g2 = new Graph("graph2");
	g->addNode("Cairo");
	g->addNode("Giza");
	g->addNode("Alex");
	g->addNode("Aswan");
	g->addNode("Fayoum");
	g->addNode("Suez");
	g->addNode("Matrouh");
	g->addNode("Luxor");

	g->addEdge("First edge", "Cairo", "Giza", 4, false);
	g->addEdge("second edge", "Giza", "Alex", 4, false);
	g->addEdge("third edge", "Alex", "Cairo", 4, false);
	g->addEdge("fourth edge", "Alex", "Matrouh", 4, true);
	g->addEdge("Fifth edge", "Matrouh", "Suez", 4, false);
	g->addEdge("six edge", "Suez", "Fayoum", 4, false);
	g->addEdge("seven edge", "Fayoum", "Matrouh", 4, false);
	g->addEdge("eight edge", "Fayoum", "Luxor", 4, false);

	/*g->addEdge("First edge", "Cairo", "Giza", 4, true);
	g->addEdge("second edge", "Giza", "Alex", 4, true);
	g->addEdge("fourth edge", "Alex", "Matrouh", 4, true);
	g->addEdge("third edge", "Alex", "Cairo", 4, true);
	g->tarjan("Cairo", "");*/
	//cout << g->LowLink["Giza"] << endl;
	cout << "third edge" << " " << g->bridge["third edge"] << endl;
	cout << "First edge" << " " << g->bridge["First edge"] << endl;
	cout << "second edge" << " " << g->bridge["second edge"] << endl;
	cout << "fourth edge" << " " << g->bridge["fourth edge"] << endl;
	cout << "Fifth edge" << " " << g->bridge["Fifth edge"] << endl;
	cout << "six edge" << " " << g->bridge["six edge"] << endl;
	cout << "seven edge" << " " << g->bridge["seven edge"] << endl;
	cout << "eight edge" << " " << g->bridge["eight edge"] << endl;


	/*g->addEdge("First edge", "Cairo", "Giza", 4, false);
	g->addEdge("second edge", "Cairo", "Alex", 4, false);
	g->addEdge("fourth edge", "Matrouh", "Cairo", 4, true);
	g->addEdge("third edge", "Alex", "Aswan", 4, false);*/
	/*cout << '\n';
	cout << g->toString();

	g->deleteNode("Cairo");

	cout << "########\n\n";
	cout << g->toString();
	
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

	cout << "nodes: " << g->nodes.size() << ", edges: " << g->edges.size() << "\n\n";*/

}


// format-> id,name,$node(i),@edge(i)
//node(i)-> name,childsnames..
//edge(i)-> name,source,destination,std::to_string(length),std::to_string(directed)
string Graph::toString() {
	string toStringNode = "$";//
	for (auto& i : nodes)
		toStringNode += i.second->to_string();

	string toStringEdges = "@";
	for (auto& i : edges)
		toStringEdges += i.second->to_string();

	string res = std::to_string(id) + "," + name + "," + toStringNode + "," + toStringEdges;

	//when load from file 
	// 
	//take first two words -> id and name
	//from after $ to before @ -> nodes loading first word after $ is the name of the node and rest of words neighbours (before @)
	//from after @ to end -> every 5 words are edgeName,source,destination,length,directed



	return res;
}


void Graph::tarjan(string node, string parent) {
	st.push(node);
	dfn[node] = LowLink[node] = ndfn;
	ndfn++;
	instack[node] = 1;
	for (auto edge : nodes[node]->edges) {
		string child;
		node == edges[edge]->destination ? child = edges[edge]->source : child = edges[edge]->destination;

		if (dfn[child] == 0) {
			tarjan(child, node);
			LowLink[node] = min(LowLink[node], LowLink[child]);

			// Mark the Articulation points
			if (LowLink[child] >= dfn[node]) {
				if (dfn[node] == 1 && root == false)
					root = true;
				else
					artPoint[node] = 1;
			}
		}
		else if (child != parent) {
			LowLink[node] = min(LowLink[node], dfn[child]);
		}
	}
	//Mark the bridges
	if (dfn[node] == LowLink[node] && parent != "") {
		for (auto e : nodes[node]->edges) {
			if (edges[e]->source == parent)
				bridge[e] = 1;
		}
	}

}