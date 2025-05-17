#include "PathFinder.h"
using namespace Model;

Model::PathFinder::PathFinder() {}

Path PathFinder::findPath(string source, string destination, unordered_map<string, Node*>& nodes, unordered_map<string, Edge*>& edges, bool isShortest)
{
    priority_queue<pair<double,  string>> pq; // {cost, {curNodeName , edgeName}}
    unordered_map<string, double> cost;
    unordered_map<string, string> parent;
    Path path;

    double sum = 1;
    for (auto const& obj : edges)
        sum += obj.second->trafficLoad;

    cost[source] = 0;
    parent[source] = "";
    pq.push({ 0, source });

    bool buildPath = false;
    string destEdge = "";
    while (!pq.empty()) {
        auto top = pq.top();
        double weight = top.first;
        string currentNode = top.second;

        pq.pop();
        weight = -weight;

        // Mission is Done !!
        if (currentNode == destination) {
            buildPath = true;
            break;
        }

        if (cost.find(currentNode) != cost.end() && weight > cost[currentNode])
            continue;

        // cout << ""
        for (const string& edge : nodes[currentNode]->edges) {
            Edge* nextEdge = edges[edge];
            string nextNode = (nextEdge->source == currentNode) ? nextEdge->destination : nextEdge->source;

            double newDist = cost[currentNode] +(isShortest ? edges[edge]->lengthCost() : edges[edge]->trafficCost(sum));
            if (cost.find(nextNode) == cost.end() || newDist < cost[nextNode]) {
                cost[nextNode] = newDist;
                parent[nextNode] = currentNode;
                destEdge = nextEdge->name;
                pq.push({ -newDist, nextNode});
            }
        }
    }

    if (buildPath)
    {
        string current = destination;
        while (current != "") {
            edges[destEdge]->trafficLoad++;
            path.Path_Nodes.push_back(current);
            current = parent[current];
        }
        reverse(path.Path_Nodes.begin(), path.Path_Nodes.end());
        path.totalCost = cost[destination];
        vector<string>& temp = path.Path_Nodes;
        for(int i = 0; i<temp.size()-1; ++i) {
            string node = temp[i];
            for(auto edge : nodes[node]->edges) {
                if(edges[edge]->source == temp[i+1] || edges[edge]->destination == temp[i+1]) {
                    path.Path_Edges.push_back(edge);
                    double cost = (isShortest? edges[edge]->lengthCost() : edges[edge]->trafficCost(sum));
                    path.totalTime += edges[edge]->getTime(cost);
                    break;
                }

            }
        }
        cout << '\n';
        for(auto i  : path.Path_Edges)
            cout << i << ' ';
        cout << '\n';
        // for(auto i  : path.Path_Nodes)
        //     cout << i << ' ';

    }
    return path;
}
