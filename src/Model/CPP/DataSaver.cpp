#ifndef DataSaver_CPP
#define DataSaver_CPP
#include "../Headers/Globals.h"
#include "../Headers/Manager.h"
#include "../CPP/FileManager.cpp"

namespace Model {
	class DataSaver {
	public:
		static void saveGraphData() {
			vector<string> fileContent;
			fileContent.push_back(to_string(Manager::getInstance().graphsCounter));
			for (auto graph : Manager::getInstance().graphs) {
				fileContent.push_back(graph->toString());
			}

			FileManager::saveToFile(fileContent, "graphData.txt");
		}
	};
}
#endif