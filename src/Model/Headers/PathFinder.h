#ifndef PATH_FINDER_H
#define PATH_FINDER_H
#include "Globals.h"
#include "../../View/PathPrinter.h"
#include "../Headers/Database.h"
#include "../Headers/PathConstructor.h"
#include "../Headers/CitiesMapperID.h"


namespace Model {

	class PathFinder {
		int from, to;
	public:
		PathFinder(int from, int to);

		pair<vector<string>, double> findPath();
	};

}
#endif