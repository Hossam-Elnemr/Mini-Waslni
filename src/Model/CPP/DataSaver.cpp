#include "../Headers/DataSaver.h"
#include "../Headers/Manager.h"
#include "../Headers/FileManager.h"


namespace Model {
	void DataSaver::saveGraphData() {
		vector<string> fileContent;
		fileContent.push_back(std::to_string(Manager::getInstance().graphsCounter));
		
		for (auto graph : Manager::getInstance().graphs) 
			fileContent.push_back(graph->toString());

		FileManager::saveToFile(fileContent, "graphData.txt");
	}

	void DataSaver::saveUserData() {
		vector<string> fileContent;		
		fileContent.push_back(std::to_string(Manager::getInstance().users.size()));
		
		for (const pair<string,User*>&  user : Manager::getInstance().users) 
			fileContent.push_back(user.second->toString());
		
		FileManager::saveToFile(fileContent, "userData.txt");
	}
}
	