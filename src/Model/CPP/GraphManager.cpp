#include "../Headers/GraphManager.h"

Model::GraphManager::GraphManager()
{
	cout << "GraphManager Constructor" << endl;
}

void Model::GraphManager::addCity(string city)
{
	/*
	* First add it in CitiesMapperID
	* get the id and put it in the graph Container that exists in Database
	*/
	int cityID = Model::CitiesMapperID::getInstance().mapCity(city);

	Model::Database::getInstance().addCity(cityID);
}

void Model::GraphManager::addEdge(string from, string to, int weight , bool isDirected)
{	
	//Validate first if the cities exist or not
	
	/*
	* First get the ids of the cities
	* Then add it in the graph Container that exists in Database
	*/
	int fromID = Model::CitiesMapperID::getIdByCity(from);
	int toID = Model::CitiesMapperID::getIdByCity(to);
	Model::Database::getInstance().addEdge(fromID, toID, weight, isDirected);
}

void Model::GraphManager::pathFinding()
{
}

Model::GraphManager::~GraphManager()
{
}
