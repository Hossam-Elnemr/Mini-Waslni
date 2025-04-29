# include "../Headers/Manager.h"

# include <string>
# include <iostream>
using namespace std;

int Manager::graphsCounter = 0;
Manager* Manager::instance = NULL;

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
	if (users.find(userName) != users.end() && users[userName] == password)
		return true;
	
	return false;
}

bool Manager::signUp(string userName, string password)
{
	if (users.find(userName) == users.end())
	{
		User user(userName, password);
		users[userName] = password;
		return true;
	}
	
	return false;
}

void Manager::editGraph(User user, int id,int op,string name,string src,string dest,double len,bool directed)
{
	if (user.editGraphCheck(id))
	{
		Graph* found = NULL;
		
			found = findGraph(id);
		if (op == 1)//Add Node
		{
			found->addNode(name);
		}
		else if (op == 2)// Add Edge
		{
			found->addEdge(name, src, dest, len, directed);
		}
		else if (op == 3)//Delete Node
		{
			found->deleteNode(name);
		}
		else //Delete Edge
		{
			found->deleteEdge(name);
		}

	}
	
}


Graph* Manager::findGraph(int id)
{
	for (auto graph : graphs)
		if (graph->getID() == id)
			return graph;
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

void Manager::addGraph(string name)
{
	Graph* newGraph = new Graph(name);
	graphs.push_back(newGraph);
	++graphsCounter;
}

