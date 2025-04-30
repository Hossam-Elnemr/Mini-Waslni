#include "../Headers/PathFinder.h"
using namespace Model;

Model::PathFinder::PathFinder() {}

Path PathFinder::findPath(string source, string destination, unordered_map<string, Node*>& nodes, unordered_map<string, Edge*>& edges, bool isShortest)
{
	priority_queue<pair<double, string>> pq;
	unordered_map<string, double> distances;
	unordered_map<string, string> parent;
	Path path;
	double sum = 0;
	for (auto const& obj : edges)
		sum += obj.second->trafficLoad;
	distances[destination] = 0;
	parent[destination] = "";
	pq.push({ 0, source });

	bool buildPath = false;
	while (!pq.empty()) {
		string currentNode;
		double weight;
		tie(weight, currentNode) = pq.top();

		pq.pop();
		weight = -weight;

		// Mission is Done !!
		if (currentNode == destination) {
			buildPath = true;
			break;
		}

		if (distances.find(currentNode) != distances.end() && weight > distances[currentNode])
			continue;

		for (const string& edge : nodes[currentNode]->edges) {
			string nextNode = edges[edge]->destination;

			double newDist = distances[currentNode] + edges[edge]->lengthCost() + (isShortest ? 0 : edges[edge]->trafficCost(sum));

			if (distances.find(nextNode) == distances.end() || newDist < distances[nextNode]) {
				distances[nextNode] = newDist;
				parent[nextNode] = currentNode;

				pq.push({ -newDist, nextNode });
			}
		}
	}

	if (buildPath)
	{
		while (destination != "") {
			path.Path_Nodes.push_back(parent[destination]);
			destination = parent[destination];
			//destination = edges[parent[destination]]->source;
		}
		reverse(path.Path_Nodes.begin(), path.Path_Nodes.end());
		path.totalCost = distances[destination];

		for (auto& edge : path.Path_Nodes)
		{
			path.Path_Edges.push_back(edges[edge]->name);
		}

		if (!isShortest)
			path.totalCost = distances[destination];
	}

	return path;
}
