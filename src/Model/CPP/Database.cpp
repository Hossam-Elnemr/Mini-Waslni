#include "../Headers/Database.h"
using namespace Model;
DynamicList Database::graphList;

Database::Database() {
	cout << "Headers::Database Constructor" << endl;
}

Database& Database::getInstance() {  
	static Database instance;
	return instance;
}

const ChildsContainer& Model::Database::getChildsOfNode(int node)
{
	//validate
	return graphList[node];
}

void Model::Database::addCity(int cityID)
{
	//validate
	graphList.setNode(cityID);
}

void Model::Database::addEdge(int from, int to, int weight , bool isDirected)
{
	//validate
	graphList[from].push_back({to, weight});
	if (!isDirected) // if the graph is undirected
		graphList[to].push_back({ from, weight }); // if the graph is undirected
}


void Database::clean()
{
}

Database::~Database()
{
	cout << "Headers::Database Destructor" << endl;
}