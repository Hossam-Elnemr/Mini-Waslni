# include "Graph.h"
#include "User.h"
# include <string>
# include <iostream>
using namespace std;
class Manager {
	static Manager* instance;
	 User* curUser;
	Manager();
public:
	vector<Graph*> graphs;
	unordered_map<string,string> users;
	static int graphsCounter;



	static Manager* getInstance() {
		if (instance == nullptr)
			instance = new Manager();
		return instance;
	}
	int totalCities();
	bool login(string userName,string password);
	bool signUp(string userName, string password);
	void editGraph(User user, int id, int op, string name, string src, string dest, double len, bool directed);
	void test();
	void addGraph(string name);
	Graph* findGraph(int id);

};
