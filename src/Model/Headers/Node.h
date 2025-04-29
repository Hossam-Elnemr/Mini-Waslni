#pragma once
# include<string>
#include<unordered_map>
using namespace std;
class Node {
public:
	string name;
	int graphId;
	Node(std::string name);
	~Node();
	unordered_map<string, bool> neighbours;
	string to_string() const noexcept;
};
