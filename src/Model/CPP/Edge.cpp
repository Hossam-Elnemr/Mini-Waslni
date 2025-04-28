# include "../Headers/Edge.h"
# include <string>
int Edge::numberofEdges = 0;
Edge::Edge(Node* src, Node* dest, std::string name, int length, bool directed) : source(src), destination(dest),
name(name), length(length), trafficLoad(0), directed(directed) {
	id = numberofEdges++;
}
void Edge::setGraphid(int graphid) {
	graphId = graphid;
}
double Edge::lengthCost() {
	return length;
}
double Edge::trafficCost() {
	return 0.0;
	/*return length*(1 + trafficLoad/graphs[graphId].traffic);*/
}

Edge::~Edge() {
	//	DO NOT DELETE SOURCE & DESTINATION
}