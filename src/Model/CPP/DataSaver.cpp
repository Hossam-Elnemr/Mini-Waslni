#include "../Headers/DataSaver.h"
#include "../Headers/Manager.h"
#include "../Headers/FileManager.h"


namespace Model {
	void DataSaver::saveGraphData() {
		vector<string> fileContent;
		fileContent.push_back(std::to_string(Manager::getInstance().graphsCounter));
		
		for (auto graph : Manager::getInstance().graphs) {
			string graphStr = graph->toString();
		
			fileContent.push_back(graphStr);
		}

		FileManager::saveToFile(fileContent, "graphData.txt");
	}
	void DataSaver::saveUserData() {
    vector<string> fileContent;
    fileContent.push_back(std::to_string(Manager::getInstance().users.size()));
    
    for (const pair<string,User*>&  user : Manager::getInstance().users) {
        string userStr = user.second->toString();
        fileContent.push_back(userStr);
    }
    
    FileManager::saveToFile(fileContent, "userData.txt");
}
}
	