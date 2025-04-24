#ifndef MINI_WASLNI_H
#define MINI_WASLNI_H
#include "Globals.h"	
#include "Database.h"
#include "CitiesMapperID.h"
#include "../../Controller/GraphManagerController.h"
class MiniWaslni {
	Controller::GraphManagerController* graphManagerController;
public:

	//Call when start the Application 
	MiniWaslni();
	void run();

	//Call here the initialization components (Database, CitiesMapper, Graph, Load Data, etc)
	void init();

	//Save the data to the file
	void close();
	~MiniWaslni();
};


#endif