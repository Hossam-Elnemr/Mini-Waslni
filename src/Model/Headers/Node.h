#pragma once
# include<string>
#include<unordered_map>
#include<unordered_set>

using namespace std;
class Node {
public:
	string name;
	int graphId;
	Node(std::string name);
	~Node();
	unordered_set<string> neighbours;
	string to_string() const noexcept;
};
