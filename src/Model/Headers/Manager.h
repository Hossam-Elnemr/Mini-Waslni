#ifndef Manager_H
#define Manager_H
# include "Graph.h"
# include "User.h"
// # include "../CPP/DataSaver.cpp"
using namespace std;
class Manager {
	static Manager instance;
	User* curUser;
	Manager();
public:
	vector<Graph*> graphs;
	unordered_map<string, string> users; // username -> password
	static int graphsCounter;

	//						User Functions
	bool login(string userName, string password);
	bool signUp(string userName, string password);

	//						Graph Functions
	int totalCities();
	void editGraph(User user, int id, int op, string name, string src, string dest, double len, bool directed);
	void addGraph(string name);
	Graph* findGraph(int id);

	//						Getters && Testing
	void test();
	static Manager& getInstance() {
		return instance;
	}
};
#endif