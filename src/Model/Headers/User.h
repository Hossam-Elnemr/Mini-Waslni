#pragma once
# include "Globals.h"
using namespace std;
class User {
	string password;
public:
    User(string userName, string password);
	int id;
	string userName;
    stack<pair<string,string>> recentSearch, undo;
	vector<int>graphsId;
    vector<std::string> history;////////////
    string getpassword();
    string toString();
	bool editGraphCheck(int id);
};
