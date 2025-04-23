# include <iostream>
#include "Manager.h"
using namespace std;
int main() {
	Manager m = Manager();
	Graph* g = m.getGraph("graph1");
	Graph* g2 = m.getGraph("graph2");
	g->addCity("Cairo");
	g->addCity("Giza");
	g->addCity("Alex");
	g->addCity("Aswan");
	g->addCity("Matrouh");
	g->addEdge("First edge", "Cairo", "Giza", 4, false);
	g->addEdge("second edge", "Cairo", "Alex", 4, false);
	g->addEdge("fourth edge", "Matrouh", "Cairo", 4, false);
	g->addEdge("third edge", "Alex", "Aswan", 4, false);
	//cout << g->roads["First edge"]->graphId;
	
	vector <string> v;
	v = g->BFS("Cairo");
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}
	//g.cities["Giza"]->to_string();
}
