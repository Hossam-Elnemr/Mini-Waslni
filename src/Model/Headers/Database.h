#ifndef DATABASE_H
#define DATABASE_H
#include <DynamicList.h>
/*
- Main DS will be here
- If we need to retrieve or modify or insert data generate the getters and setters (make more validation)
*/


class Database {
	Database() = default;
	static Database* instance;
	static DynamicList graph; 
public:
	
	static Database& getInstance();

	Database(const Database&) = delete;
	Database(const Database&&) = delete;
	Database& operator=(const Database&) = delete;
	Database& operator=(const Database&&) = delete;
	~Database() = default;
};


#endif