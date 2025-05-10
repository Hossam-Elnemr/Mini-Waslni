#include "Model/Headers/Manager.h"
#include "Model/Headers/DataSaver.h"
#include "Model/Headers/DataLoader.h"
#include "Model/Headers/FileManager.h"
#include "Model/Headers/PathFinder.h"

void sampleGraphTest() {

	Manager::getInstance().addGraph("Cairo Metro");
	Manager::getInstance().graphs.back()->addNode("Helwan");
	Manager::getInstance().graphs.back()->addNode("Maadi");
	Manager::getInstance().graphs.back()->addNode("Sadat");
	Manager::getInstance().graphs.back()->addNode("Attaba");
	Manager::getInstance().graphs.back()->addEdge("Line1HM", "Helwan", "Maadi", 8.5, false);
	Manager::getInstance().graphs.back()->addEdge("Line1MS", "Maadi", "Sadat", 6.2, false);
	Manager::getInstance().graphs.back()->addEdge("Line1SA", "Sadat", "Attaba", 2.1, false);
	
	Manager::getInstance().addGraph("Alex Tram");
	Manager::getInstance().graphs.back()->addNode("Raml");
	Manager::getInstance().graphs.back()->addNode("Sidi Gaber"); 
	Manager::getInstance().graphs.back()->addNode("Miami");
	Manager::getInstance().graphs.back()->addEdge("Route1RS", "Raml", "Sidi Gaber", 5.3, false);
	Manager::getInstance().graphs.back()->addEdge("Route1SM", "Sidi Gaber", "Miami", 7.8, false);
	
}


void sampleUserTest() {
   
    User* user1 = new User("john_doe", "password123");
    user1->recentSearch.push("Cairo");
    user1->recentSearch.push("Alexandria");
    user1->graphsId.push_back(1);
    user1->graphsId.push_back(2);
    
    User* user2 = new User("jane_smith", "secure456");
    user2->recentSearch.push("Giza");
    user2->graphsId.push_back(3);
    
    Manager::getInstance().users["john_doe"] = user1;
    Manager::getInstance().users["jane_smith"] = user2;
}

void loadGraphTest() {
	vector<string> fileContent = Model::FileManager::readFromFile("graphData.txt");
	cout << "File content size: " << fileContent.size() << "\n";
	if (!fileContent.empty()) {
		cout << "1ST line: " << fileContent[0] << "\n";
	}
	Model::DataLoader::loadGraphsFromFile(fileContent);
	cout << "Finished loadGraphTest\n";
}

void loadUserTest() {
	vector<string> fileContent = Model::FileManager::readFromFile("userData.txt");
	Model::DataLoader::loadUsersFromFile(fileContent);
	cout << "Finished loadUserTest\n";
}

void testPathFinder() {
    Manager::getInstance().addGraph("Test Path Graph");
    Graph* graph = Manager::getInstance().graphs.back();
    
    graph->addNode("A");
    graph->addNode("B");
    graph->addNode("C");
    graph->addNode("D");
    graph->addNode("E");
    
    graph->addEdge("AB", "A", "B", 2, false);  
    graph->addEdge("BC", "B", "C", 5, false);   
    graph->addEdge("CD", "C", "D", 2, false);   
    graph->addEdge("DE", "D", "E", 5, false);  
    graph->addEdge("AE", "A", "E", 20, false);  
    
    graph->edges["AB"]->trafficLoad = 0.5;  
    graph->edges["BC"]->trafficLoad = 0.2;  
    graph->edges["CD"]->trafficLoad = 0.8;  
    graph->edges["DE"]->trafficLoad = 0.3;  
    graph->edges["AE"]->trafficLoad = 0.1;  
    
    cout << "\nTesting Path Finder:\n";
    cout << "====================\n";    
    Model::PathFinder pathFinder;

    cout << "\nShortest Path from A to E (distance only):\n";
    Path shortestPath = pathFinder.findPath("A", "E", graph->nodes, graph->edges, true);
    cout << "Path: ";
    for (const string& edge : shortestPath.Path_Edges) 
        cout << edge << " -> ";
    cout << "END\n";
    cout << "Total Distance: " << shortestPath.totalCost << " units\n";

    cout << "\nFastest Path from A to E (considering traffic):\n";
    Path fastestPath = pathFinder.findPath("A", "E", graph->nodes, graph->edges, false);
    cout << "Path: ";
    for (const string& edge : fastestPath.Path_Edges) 
        cout << edge << " -> ";
    
    cout << "END\n";
    cout << "Total Cost (distance + traffic): " << fastestPath.totalCost << " units\n";
}

int main() {
	Manager m = Manager::getInstance();
	// testPathFinder();
	// loadGraphTest();
	// loadUserTest();
	// // sampleUserTest();
	// // Graph::test();
	// Model::DataSaver::saveGraphData();
	// Model::DataSaver::saveUserData();
	// cout << Manager::getInstance().users.size() << "\n";
	// for (const pair<string,User*>& user : Manager::getInstance().users) {
	// 	cout << user.second->toString() << "\n";
	// }

}