#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H
/* 
* This class is an abstraction of graph data structure
* In future, if we need to change the DS and the logic => we need only to change this class :)
* Instead of changing the whole code
*/
class DynamicList {
//this defines Editable
#define GRAPH vector<vector<pair<int,int>>> 
#define ChildsContainer vector<pair<int,int>>
#define NODE int 

	GRAPH graph; //setter & getter to access on it
public:

	DynamicList() = default;

	//Operator Overloading : act as adj[node] => access on chlids container
	//Now we don't care about HOW => we just care about WHAT :)
	ChildsContainer& operator[](int node) const noexcept;

	NODE getNode(int node) const noexcept;
	void setNode(NODE node) noexcept;

	//....

	DynamicList(const DynamicList&) = delete;
	DynamicList(const DynamicList&&) = delete;
	DynamicList& operator=(const DynamicList&) = delete;
	~DynamicList();
};


#endif