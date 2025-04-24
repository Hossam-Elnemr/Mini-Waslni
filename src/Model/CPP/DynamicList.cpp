#include "../Headers/DynamicList.h"

DynamicList::DynamicList() : graph(vector<vector<pair<int,int>>>())
{
	cout << "Headers::DynamicList Constructor" << endl;
}

ChildsContainer& DynamicList::operator[](int node) noexcept  
{  
	return graph[node];  
}

void DynamicList::setNode(NODE node) noexcept
{
	if (node >= graph.size()) {
		graph.push_back(vector<pair<int, int>>());
	}
	else {
		graph[node].clear(); // act as a new node added
	}
}

DynamicList::~DynamicList()
{
	cout << "Headers::DynamicList Destructor" << endl;
	for (auto& i : graph) {
		i.clear();
	}
	graph.clear();
}
