#include "User.h"

User::User(string userName, string password)
{
	this->userName = userName;
	this->password = password;
}




bool User::editGraphCheck(int id)
{
	for (auto it : graphsId)
		if (it == id)return true;
	
	return false;
}
