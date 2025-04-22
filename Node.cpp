# include<iostream>
# include "Node.h"
using namespace std;
int Node::numberOfNodes = 0;
Node::Node(string name) {
	this->name = name;
	id = numberOfNodes++;
}
void Node::to_string() {
	cout << "ID: " << id << "\nName: " << name << "\nNeighbours: ";
	for (auto i : neighbours)
		cout << i << ' ';
	cout << '\n';
}
Node::~Node() {
	neighbours.clear();
}
void Node::addNeighbour(string name) {
	neighbours.insert(name);
}
