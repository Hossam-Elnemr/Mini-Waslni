# include "../Headers/Node.h"
int Node::numberOfNodes = 0;
Node::Node(string name) {
	this->name = name;
	id = numberOfNodes++;
}
string Node::to_string() {
	string str = "ID: " + std::to_string(id) + "\nName: " + name + "\nNeighbours: ";
	for (auto i : neighbours)
		str += i + ' ';
	return str;
}
Node::~Node() {
	neighbours.clear();
}
void Node::addNeighbour(string name) {
	neighbours.insert(name);
}