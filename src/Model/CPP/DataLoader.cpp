#ifndef DataLoader_CPP
#define DataLoader_CPP
#include "../Headers/Globals.h"
#include "../Headers/Manager.h"
#include "../CPP/FileManager.cpp"
#include "../Headers/Graph.h"
namespace Model {
	class DataLoader {
	public: 
        static void loadGraphsFromFile(const vector<string>& fileContent) {
            if (fileContent.empty()) {
                cerr << "File content is empty!\n";
                return;
            }

            int graphsNo = stoi(fileContent[0]);

            for (int i = 1; i < fileContent.size(); ++i) {
                istringstream graphStream(fileContent[i]);
                string id, graphName;
                vector<vector<string>> nodes , edges;

                getline(graphStream, id, ',');
                getline(graphStream, graphName, ',');

                int graphId = std::stoi(id);


                string interval;
                while (getline(graphStream, interval, '@')) {
                    //[$ to @]
                    if (interval[0] == '$') {
                        istringstream nodeInfoInterval(interval.substr(1));
                        string nodeName;

                        while (std::getline(nodeInfoInterval, nodeName, ',')) {
                            vector<string> nodeData;
                            nodeData.push_back(nodeName);

                            std::string neighbor;
                            while (std::getline(nodeInfoInterval, neighbor, ',')) {
                                nodeData.push_back(neighbor);
                            }

                            nodes.push_back(nodeData);
                        }
                    }
                    else {
                        //(after @)
                        std::istringstream edgeInfoInterval(interval);
                        std::string edgeName, source, destination, lengthStr, isDirected;

                        while (std::getline(edgeInfoInterval, edgeName, ',')) {
                            std::getline(edgeInfoInterval, source, ',');
                            std::getline(edgeInfoInterval, destination, ',');
                            std::getline(edgeInfoInterval, lengthStr, ',');
                            std::getline(edgeInfoInterval, isDirected, ',');

                            vector<string> edgeData = { edgeName, source, destination, lengthStr, isDirected };
                            edges.push_back(edgeData);
                        }
                    }
                }

                Graph* graph = new Graph(graphId, graphName, nodes, edges);
				Manager::getInstance().graphs.push_back(graph);

                //for testing
                cout << "Graph " << graphName << " with ID " << graphId << " loaded successfully.\n";
            }
        }


		
	};
}


#endif