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
}
	