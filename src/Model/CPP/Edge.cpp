# include "../Headers/Edge.h"
int Edge::numberofEdges = 0;
Edge::Edge(std::string name, std::string src, std::string dest, int length, bool directed, int id, int graphId, double trafficLoad) : source(src), destination(dest),
name(name), length(length), directed(directed) , id(id), graphId(graphId) , trafficLoad(trafficLoad){
	id = numberofEdges++;
}
void Edge::setGraphid(int graphid) {
	graphId = graphid;
}
double Edge::lengthCost() {
	return length;
}
string Edge::to_string() const {
	return  name + "," + source + "," + destination + "," + std::to_string(length) + "," + std::to_string(directed) + "," + std::to_string(id) + "," + std::to_string(graphId) + "," + std::to_string(trafficLoad) +",";
}
double Edge::trafficCost(double sum) {
	return length*(1 + trafficLoad/sum);
}

Edge::~Edge() {
	//	DO NOT DELETE SOURCE & DESTINATION
}