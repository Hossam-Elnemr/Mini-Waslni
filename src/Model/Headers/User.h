#ifndef User_H
#define User_H
# include "Globals.h"
using namespace std;
class User {
	string password;
public:
	int id;
	string userName;
	stack<string> recentSearch, undo;
	vector<int>graphsId;

	User(string userName, string password);
	bool editGraphCheck(int id);
};
#endif