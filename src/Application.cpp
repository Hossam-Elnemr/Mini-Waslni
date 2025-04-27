/*# include <iostream>
#include "Model/Headers/MiniWaslni.h"
int main() {
	MiniWaslni app;
	app.run();
	//cout << "Hello";
}*/

# include <iostream>
#include "Manager.h"
using namespace std;
int main() {
	Manager* m = Manager::getInstance();
	Graph::test();
}
