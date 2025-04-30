#include "../Headers/MiniWaslni.h"

MiniWaslni::MiniWaslni()
{
	init();
}

void MiniWaslni::run()
{
	cout << "Welcome to Mini Waslni Application\n";
	int choice;

	do {		choice = graphManagerController->showMenu();
		if (choice == 1) {
			graphManagerController->addGraph();
		}
		else if (choice == 6) {
			graphManagerController->pathFinding();
		}
	} while (choice != 7);

	
}

void MiniWaslni::init()
{
	//Initialize the components
	Model::Database::getInstance();
	Model::CitiesMapperID::getInstance();
	graphManagerController = new Controller::GraphManagerController();
	
	cout << "Headers::MiniWaslni init" << endl;
}

void MiniWaslni::close()
{
	Model::Database::clean();
	if (graphManagerController != nullptr) {
		delete graphManagerController;
		graphManagerController = nullptr;
	}

}


MiniWaslni::~MiniWaslni()
{
	close();
	cout << "Headers::MiniWaslni Destructor" << endl;
}