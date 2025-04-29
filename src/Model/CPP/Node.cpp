# include<iostream>
# include "Node.h"
using namespace std;
Node::Node(string name) {
	this->name = name;
	cout << '\n';
	cout << name << '\n';
}
string Node::to_string() const noexcept{
	string str = "Name: " + name + "\nNeighbours: ";
	for (auto& i : neighbours)
		str += i.first + ' ';
	return str;
}
Node::~Node() {
	neighbours.clear();
}
