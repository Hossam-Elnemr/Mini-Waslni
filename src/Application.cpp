#include "Model/Headers/Manager.h"
#include "Model/Headers/DataSaver.h"
#include "Model/Headers/DataLoader.h"
#include "Model/Headers/FileManager.h"
void sampleTest() {

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

void loadGraphTest() {
	vector<string> fileContent = Model::FileManager::readFromFile("graphData.txt");
	cout << "File content size: " << fileContent.size() << "\n";
	if (!fileContent.empty()) {
		cout << "1ST line: " << fileContent[0] << "\n";
	}
	Model::DataLoader::loadGraphsFromFile(fileContent);
	cout << "Finished loadGraphTest\n";
}

int main() {
	Manager m = Manager::getInstance();
	loadGraphTest();
	
	// Graph::test();
	Model::DataSaver::saveGraphData();


}