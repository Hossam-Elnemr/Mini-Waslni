# include<iostream>
# include "Node.h"
using namespace std;
int Node::numberOfNodes = 0;
Node::Node(string name) {
	this->name = name;
	id = numberOfNodes++;
}
string Node::to_string() const noexcept {
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
