#include "PathPrinter.h"

void View::PathPrinter::printPath(const vector<string>& path, double distance) const noexcept {
	cout << "Shortest Path: ";

	for (int i = 0; i < path.size(); i++) {
		cout << path[i];
		if (i != path.size() - 1)
			cout << " -> ";
		else
			cout << endl;
	}
	
	cout << "\nDistance: " << distance << endl;
}
