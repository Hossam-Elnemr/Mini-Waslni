#pragma once
#ifndef DataSaver_H
#define DataSaver_H
#include "Globals.h"
#include "Manager.h"
#include "FileManager.h"
namespace Model {
	class DataSaver {
	public:
        static void saveGraphData() {
            vector<string> fileContent;
            fileContent.push_back(std::to_string(Manager::getInstance()->graphsCounter));

            for (auto graph : Manager::getInstance()->graphs)
                fileContent.push_back(graph->toString());

            FileManager::saveToFile(fileContent, "graphData.txt");
        }
        static void saveUserData() {
            vector<string> fileContent;
            fileContent.push_back(std::to_string(Manager::getInstance()->users.size()));

            for (const pair<string,User*>&  user : Manager::getInstance()->users)
                fileContent.push_back(user.second->toString());

            FileManager::saveToFile(fileContent, "userData.txt");
        }
        static void save() {
            saveGraphData();
            saveUserData();
        }
	};
}
#endif
