# include "Manager.h"

int Manager::graphsCounter = 0;
int Manager::usersCounter = 0;
Graph* Manager::curGraph = NULL;
User* Manager::curUser = NULL;
Manager* Manager:: instance = NULL;
Manager::Manager() {
	
}
int Manager::totalCities() {
	int sum = 0;
	for (auto graph : graphs)
		sum += (int)graph->nodes.size();
	return sum;
}

bool Manager::login(string userName, string password)
{
    if (usersInfo.find(userName) != usersInfo.end() && usersInfo[userName] == password){
        curUser = users[userName];
        cerr << "Here: &&&&& " << curUser->userName << ' ' << curUser->getpassword() << '\n';
		return true;
    }
	return false;
}

bool Manager::signUp(string userName, string password)
{
    curUser = addUser(userName, password);
    usersInfo[userName] = password;
    users[userName] = curUser;
    return true;
}

void Manager::editGraph(User user, int id, int op, string name, string src, string dest, double len, bool directed)
{
	if (user.editGraphCheck(id))
	{
		Graph* found = NULL;

        found = findGraph(id, "");
		if (op == 1) //Add Node
		{
			found->addNode(name);
		}
		else if (op == 2) // Add Edge
		{
			found->addEdge(name, src, dest, len, directed);
		}
		else if (op == 3) //Delete Node
		{
			found->deleteNode(name);
		}
		else //Delete Edge
		{
			found->deleteEdge(name);
		}

	}

}


Graph* Manager::findGraph(int id, string name) {
	for (auto graph : graphs)
        if (graph->getID() == id || Tools::isEqual(graph->getName(), name))
            return cout << "Found\n", graph;
    cout << graphsCounter << '\n';
	return NULL;
}
User* Manager::findUser(string username)
{
    for(auto it:users)
        if(Tools::isEqual(it.first, username))
            return it.second;
    return NULL;
}
void Manager::test()
{
	int choice;
	do {
		cout << " Login Press 1\nSign up press 2 \nExis press 0\n";

		cin >> choice;
		string username, pass;
		cout << "Enter Username:   ";
		cin >> username;
		cout << "Enter password:   ";
		cin >> pass;

		if (choice == 1)
		{
			if (login(username, pass))
				cout << "success\n";
			else
				cout << "	WRONG USERNAME OR PASSWORD	!!!!!!!\n";
		}
		else
		{
			if (!signUp(username, pass))
				cout << "This username exists :D\n";
		}
	} while (choice != 0);
}


Graph* Manager::addGraph(string name)
{
	Graph* newGraph = new Graph(name);
	graphs.push_back(newGraph);
    curUser->graphsId.push_back(newGraph->getID());
    cout << "sz: " << graphs.size() << '\n';
	++graphsCounter;
    return newGraph;
}
User* Manager::addUser(string name, string password)
{
    User* newUser = new User(name, password);
    users[name] = newUser;
    ++usersCounter;
    return newUser;
}
// void Manager::addFromFile(int graphId, std::string graphName, vector<vector<string>> nodes, vector<vector<string>> edges) {
//     Graph* insertedGraph = new Graph(graphId, graphName, nodes, edges);
//     graphs.push_back(insertedGraph);
//     ++graphsCounter;
// }
void Manager::testGraph() {
    if(curGraph == NULL)
        return;
   // curGraph->testMe();
}
void Manager::start() {
    addGraph("Me");
    addGraph("New");
    // cout << "Select a graph: \n";
    // for(auto i : graphs)
    //     cout << i->getName() << ' ';
    string name; cin >> name;
    Graph* desiredGraph = findGraph(-1, name);
    enterGraph(desiredGraph);

    testGraph();
    // graphs.back()->testMe();
    cout << graphsCounter << '\n';
}
void Manager::enterGraph(Graph* graph) {
    if(graph == nullptr)
        return cout << "\nEnter a valid graph!\n", void();
    cout << "You entered " << graph->getName() << " successfully\n";
    curGraph = graph;
}
