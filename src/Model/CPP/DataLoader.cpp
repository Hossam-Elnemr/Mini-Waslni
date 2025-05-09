#ifndef DataLoader_CPP
#define DataLoader_CPP
#include "../Headers/Manager.h"
#include "../CPP/FileManager.cpp"
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
                istringstream graphIss(fileContent[i]);
                string id, graphName,root,ndfn;
                vector<vector<string>> nodes , edges;

                #define _ getline

                _(graphIss, id, ',');
                _(graphIss, graphName, ',');
                _(graphIss, root, ',');
                _(graphIss, ndfn, ',');
                

                int graphId = std::stoi(id);
                bool graphRoot = std::stoi(root);
                int graphNdfn = std::stoi(ndfn);
                

                string interval;
                while (_(graphIss, interval, '@')) { 
                    //[$ to @]
                    if (interval[0] == '$') {
                        istringstream allNodesInfoIss(interval.substr(2));///ignore $~
                        
                        string nodeInfo;
                        while (_(allNodesInfoIss, nodeInfo, '~')) {
                            //load node info and it's edges here
                            istringstream nodeInfoIss(nodeInfo);
                            vector<string> nodeData;
                            string id, name;
                            _(nodeInfoIss, id, ',');
                            _(nodeInfoIss, name, ',');

                            nodeData.push_back(id);
                            nodeData.push_back(name);


                            std::string neighbor;
                            while (_(nodeInfoIss, neighbor, ',')) {
                                nodeData.push_back(neighbor);
                            }

                            nodes.push_back(nodeData);
                        }
                    }
                    else {
                        //(after @)
                        istringstream edgeInfoInterval(interval);
                        string edgeName, source, destination, length, isDirected, id,graphId,trafficLoad;

                        while (_(edgeInfoInterval, edgeName, ',')) {
                            _(edgeInfoInterval, source, ',');
                            _(edgeInfoInterval, destination, ',');
                            _(edgeInfoInterval, length, ',');
                            _(edgeInfoInterval, isDirected, ',');
                            _(edgeInfoInterval, id, ',');
                            _(edgeInfoInterval, graphId, ',');
                            _(edgeInfoInterval, trafficLoad, ',');


                            vector<string> edgeData = { edgeName, source, destination, length, isDirected,id,graphId,trafficLoad };
                            edges.push_back(edgeData);
                        }
                    }
                }

                Graph* graph = new Graph(graphId, graphName ,graphRoot , graphNdfn, nodes, edges);
				Manager::getInstance().graphs.push_back(graph);

                //for testing
                cout << "Graph " << graphName << " with ID " << graphId << " loaded successfully.\n";
            }
        }


		
	};
}


#endif