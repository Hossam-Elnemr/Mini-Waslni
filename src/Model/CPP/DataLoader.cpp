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
