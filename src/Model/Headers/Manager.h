#pragma once
# include "Graph.h"
# include "User.h"
using namespace std;
class Manager {
    static Manager* instance;

	Manager();
public:
    static User* curUser;
    static Graph* curGraph;
	vector<Graph*> graphs;
    unordered_map<string, User*> users;
    unordered_map<string, string> usersInfo; // username -> password
	static int graphsCounter;
    static int usersCounter;

	//						User Functions
    User* addUser(string userName, string password);
	bool login(string userName, string password);
	bool signUp(string userName, string password);

	//						Graph Functions
    Graph* addGraph(string name);
    void editGraph(User user, int id, int op, string name, string src, string dest, double len, bool directed);
    void enterGraph(Graph* graph);
    int totalCities();
    void addFromFile(int graphId, string graphName, vector<vector<string>> nodes, vector<vector<string>> edges);
    Graph* findGraph(int id, string name);
    User* findUser(string username);

	//						Getters && Testing
	void test();
    static void testGraph();
    static Manager* getInstance() {
        if(instance == NULL)
            instance = new Manager();
		return instance;
	}
    void start();
};
