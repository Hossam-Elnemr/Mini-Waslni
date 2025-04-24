#ifndef DATABASE_H
#define DATABASE_H
#include "Globals.h"
#include "DynamicList.h"
namespace Model {
	/*
	- Main DS will be here
	- If we need to retrieve or modify or insert data generate the getters and setters (make more validation)
	*/

	class Database {
		static DynamicList graphList; // Declare the container as a static pointer  

		Database();
	public:

		static Database& getInstance();



		Database(const Database&) = delete;
		Database(const Database&&) = delete;
		Database& operator=(const Database&) = delete;
		Database& operator=(const Database&&) = delete;

		static void clean();
		~Database();

	};

}
#endif