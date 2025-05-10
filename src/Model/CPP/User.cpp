#include "../Headers/User.h"
User::User(string userName, string password) {
	this->userName = userName;
	this->password = password;
}

bool User::editGraphCheck(int id) {
	for (auto it : graphsId)
		if (it == id)return true;
	return false;
}

//to save in file
//format: userName password
string User::toString() {
	string result = std::to_string(id) + "," + userName + "," + password;
    
    result += "$";
    stack<string> tempStack = recentSearch;
    while (!tempStack.empty()) {
        result += tempStack.top() + ",";
        tempStack.pop();
    }
    
    result += "@";
    tempStack = undo;
    while (!tempStack.empty()) {
        result += tempStack.top() + ",";
        tempStack.pop();
    }
		
    result += "#";
    for (int graphId : graphsId) {
        result += std::to_string(graphId) + ",";
    }
    
    return result;
}

string User::getPassword() {
	return password;
}