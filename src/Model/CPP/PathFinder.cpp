#include "../Headers/PathFinder.h"
using namespace Model;

Model::PathFinder::PathFinder() {}

Path PathFinder::findPath(string source, string destination, unordered_map<string, Node*>& nodes, unordered_map<string, Edge*>& edges, bool isShortest)
{
	priority_queue<pair<double, pair<string ,string>>> pq; // {cost, {curNodeName , edgeName}}
	unordered_map<string, double> distances;
	unordered_map<string, string> parent;
	Path path;
	
	double sum = 0;
	for (auto const& obj : edges)
		sum += obj.second->trafficLoad;

	distances[source] = 0;
	parent[source] = "";
	pq.push({ 0, {source , ""}});

	bool buildPath = false;
	string destEdge = "";

	while (!pq.empty()) {
		auto top = pq.top();
		double weight = top.first;
		string currentNode = top.second.first;
		string currentEdge = top.second.second;
		
		pq.pop();
		weight = -weight;

		// Mission is Done !!
		if (currentNode == destination) {
			buildPath = true;
			destEdge = currentEdge;
			break;
		}

		if (distances.find(currentNode) != distances.end() && weight > distances[currentNode])
			continue;

		for (const string& edge : nodes[currentNode]->edges) {
			Edge* nextEdge = edges[edge];

			double newDist = distances[currentNode] + edges[edge]->lengthCost() + (isShortest ? 0 : edges[edge]->trafficCost(sum));
			
			if (distances.find(nextEdge->destination) == distances.end() || newDist < distances[nextEdge->destination]) {
				distances[nextEdge->destination] = newDist;
				parent[nextEdge->name] = currentEdge;
				destEdge = nextEdge->name;
				pq.push({ -newDist, {nextEdge->destination , nextEdge->name} });
			}
		}
	}

	if (buildPath)
	{
		while (destEdge != "") {
			path.Path_Edges.push_back(destEdge);
			destEdge = parent[destEdge];
		}
		reverse(path.Path_Edges.begin(), path.Path_Edges.end());

		path.totalCost = distances[destination];

		if (!isShortest)
			path.totalCost = distances[destination];
	}

	return path;
}
