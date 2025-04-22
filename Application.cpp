# include <iostream>
#include "Manager.h"
using namespace std;
int main() {
	Manager m = Manager();
	Graph* g = m.getGraph("graph1");
	Graph* g2 = m.getGraph("graph2");
	g->addCity("Cairo");
	g->addCity("Giza");
	g->addEdge("First edge", "Cairo", "Giza", 4, false);
	cout << g->roads["First edge"]->graphId;
	//g.cities["Giza"]->to_string();
}
