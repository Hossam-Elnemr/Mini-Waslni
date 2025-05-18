#pragma once
#ifndef DataLoader_H
#define DataLoader_H
#include "Globals.h"
#include "Manager.h"
#include "FileManager.h"

namespace Model {
	class DataLoader {
	public: 
        static void loadGraphsFromFile(const vector<string>& fileContent) ;
		static void loadUsersFromFile(const vector<string>& fileContent);
        static void loadGraphs() {
            vector<string> fileContent = Model::FileManager::readFromFile("graphData.txt");
            // cout << "File content size: " << fileContent.size() << "\n";
            Model::DataLoader::loadGraphsFromFile(fileContent);
        }
        static void loadUsers() {
            vector<string> fileContent = Model::FileManager::readFromFile("userData.txt");
            Model::DataLoader::loadUsersFromFile(fileContent);
            cout << "Finished loadUserTest\n";
        }
        static void load() {
            loadGraphs();
            loadUsers();
        }
	};
}
#endif
