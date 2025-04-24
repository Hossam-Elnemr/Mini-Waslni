#include "../Headers/Database.h"
using namespace Model;
DynamicList Database::graphList;

Database::Database() {
	cout << "Headers::Database Constructor" << endl;
}

Database& Database::getInstance() {  
	static Database instance;
	return instance;
}


void Database::clean()
{
}

Database::~Database()
{
	cout << "Headers::Database Destructor" << endl;
}