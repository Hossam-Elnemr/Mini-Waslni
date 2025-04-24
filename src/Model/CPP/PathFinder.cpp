#include "../Headers/PathFinder.h"
using namespace Model;

Model::PathFinder::PathFinder(int from, int to) : from(from), to(to) {}

pair<vector<string>, double>& PathFinder::findPath()
{
	unordered_map<int, double> distances;
	unordered_map<int, int> parent;
	priority_queue<pair<double, int>> pq;
	
	distances[from] = 0;
	parent[from] = -1;
	pq.push({ 0, from });

	bool buildPath = false;
	while (!pq.empty()) {
		int currentNode, weight;
		tie(weight, currentNode) = pq.top();
		pq.pop();
		weight = -weight;

		// Mission is Done !!
		if (currentNode == to) {
			buildPath = true;
			break;
		}

		if (distances.find(currentNode) != distances.end())
			continue;

		for (const auto& childs : Model::Database::getInstance().getChildsOfNode(currentNode)) {
			double newDist = distances[currentNode] + childs.second; 
			if (newDist < distances[childs.first]) {
				distances[childs.first] = newDist;
				parent[childs.first] = currentNode;
				pq.push({ -newDist, childs.first });
			}
		}
	}

	pair<vector<string>, double> ret;
	if(!buildPath)
		ret = { {}, -1 };
	else {
		Model::PathConstructor pathConstructor;
		ret = { pathConstructor.constructPath(from, to, parent) , distances[to] };
	}
	return ret;
}

