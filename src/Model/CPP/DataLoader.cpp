#include "../Headers/DataLoader.h"
#include "../Headers/Manager.h"
#include "../Headers/FileManager.h"
using namespace std;
using namespace Model;

void DataLoader::loadGraphsFromFile(const vector<string>& fileContent) {
    if (fileContent.empty()) {
        cerr << "File content is empty!\n";
        return;
    }

    try {
        int graphsNo = stoi(fileContent[0]);
        Graph::numberOfGraphs = graphsNo;

        
        for (int i = 1; i < fileContent.size(); ++i) {
            string line = fileContent[i];
            int dollarPos = line.find('$');
            int atPos = line.find('@');
            
            // Parse header
            string headerPart = line.substr(0, dollarPos);
            istringstream headerIss(headerPart);
            string id, graphName, root, ndfn;
            
            if (!getline(headerIss, id, ',') || 
                !getline(headerIss, graphName, ',') || 
                !getline(headerIss, root, ',') || 
                !getline(headerIss, ndfn, ',')) {
                cerr << "Error: Invalid header format\n";
                continue;
            }


            int graphId = stoi(id);
            bool graphRoot = (root == "1");
            int graphNdfn = stoi(ndfn);

            vector<vector<string>> nodes, edges;

            // Node Part
            string nodePart = line.substr(dollarPos + 2, atPos - dollarPos - 2);
            istringstream nodeIss(nodePart);
            string nodeInfo;
                
            while (getline(nodeIss, nodeInfo, '~')) {
                istringstream nodeDetailIss(nodeInfo);
                vector<string> nodeData;
                string nodeId, nodeName;
                
                if (!getline(nodeDetailIss, nodeId, ',') || 
                    !getline(nodeDetailIss, nodeName, ',')) {
                    cerr << "Error: Invalid node format\n";
                    continue;
                }

                
                nodeData.push_back(nodeId);
                nodeData.push_back(nodeName);

                string edgeName;
                while (getline(nodeDetailIss, edgeName, ',')) {
                    if (!edgeName.empty()) {
                        nodeData.push_back(edgeName);
                    }
                }

                nodes.push_back(nodeData);
            }

            // Edge Part
            string edgePart = line.substr(atPos + 1);
            istringstream edgeIss(edgePart);
            string edgeInfo;
            
            while (!edgeIss.eof()) {
                string edgeName, source, destination, length, isDirected, edgeId, edgeGraphId, trafficLoad;
                
                if (!getline(edgeIss, edgeName, ',') || 
                    !getline(edgeIss, source, ',') || 
                    !getline(edgeIss, destination, ',') || 
                    !getline(edgeIss, length, ',') || 
                    !getline(edgeIss, isDirected, ',') || 
                    !getline(edgeIss, edgeId, ',') || 
                    !getline(edgeIss, edgeGraphId, ',') || 
                    !getline(edgeIss, trafficLoad, ',')) {
                    if (!edgeName.empty()) {
                        cerr << "Error: Invalid edge format\n";
                    }
                    break;
                }

                vector<string> edgeData = {edgeName, source, destination, length, isDirected, edgeId, edgeGraphId, trafficLoad};
                edges.push_back(edgeData);
            }

            Graph* graph = new Graph(graphId, graphName, graphRoot, graphNdfn, nodes, edges);
            Manager::getInstance().graphs.push_back(graph);
        }
        cout << "loaded graphs\n";
        Manager::getInstance().graphsCounter = graphsNo;
        Graph::numberOfGraphs = graphsNo;

    }
    catch (const std::exception& e) {
        cerr << "Error loading graphs: " << e.what() << "\n";
    }
}


void DataLoader::loadUsersFromFile(const vector<string>& fileContent) {
    if (fileContent.empty()) {
        cerr << "File content is empty!\n";
        return;
    }

    try {
        int usersNo = stoi(fileContent[0]);
        
        for (int i = 1; i < fileContent.size(); ++i) {
            string line = fileContent[i];
            
            //Main user info part
            int dollarPos = line.find('$');
            string mainInfo = line.substr(0, dollarPos);
            istringstream mainIss(mainInfo);
            string id, userName, password;
            
            if (!getline(mainIss, id, ',') || 
                !getline(mainIss, userName, ',') || 
                !getline(mainIss, password, ',')) {
                cerr << "Error: Invalid user format\n";
                continue;
            }

            
            User* user = new User(userName, password);
            user->id = stoi(id);

            //Recent searches stack part
            int atPos = line.find('@');
            string recentSearches = line.substr(dollarPos + 1, atPos - dollarPos - 1);
            istringstream searchIss(recentSearches);
            string search;
            while (getline(searchIss, search, ',')) 
                if (!search.empty()) 
                    user->recentSearch.push(search);

            // Undo stack part
            int hashPos = line.find('#');
            string undoStack = line.substr(atPos + 1, hashPos - atPos - 1);
            istringstream undoIss(undoStack);
            string undoItem;
            while (getline(undoIss, undoItem, ',')) {
                if (!undoItem.empty()) {
                    user->undo.push(undoItem);
                }
            }

            // Graph IDs part
            string graphIds = line.substr(hashPos + 1);
            istringstream graphIss(graphIds);
            string graphId;

            while (getline(graphIss, graphId, ',')) 
                if (!graphId.empty()) 
                    user->graphsId.push_back(stoi(graphId));
                
            

            Manager::getInstance().users[userName] = user;
        }
        cout << "Loaded users\n";
    }
    catch (const std::exception& e) {
        cerr << "Error loading users: " << e.what() << "\n";
    }
}