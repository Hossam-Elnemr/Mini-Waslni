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
		static DynamicList graphList;  

		Database();
	public:

		static Database& getInstance();
		static const ChildsContainer& getChildsOfNode(int id);
		static void addCity(int cityID);
		static void addEdge(int from, int to, int weight , bool isDirected);



		Database(const Database&) = delete;
		Database(const Database&&) = delete;
		Database& operator=(const Database&) = delete;
		Database& operator=(const Database&&) = delete;

		static void clean();
		~Database();

	};

}
#endif