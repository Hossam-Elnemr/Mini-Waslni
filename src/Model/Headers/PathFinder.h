#ifndef PATH_FINDER_H
#define PATH_FINDER_H
#include "Globals.h"
#include "../../View/PathPrinter.h"
#include "../Headers/Database.h"
#include "../Headers/PathConstructor.h"
#include "../Headers/CitiesMapperID.h"
#include "../Headers/Path.h"
#include "../Headers/Node.h"
#include "../Headers/Edge.h"

namespace Model {

	class PathFinder {
	public:
		PathFinder();

		Path findPath(string source , string destination, unordered_map<string, Node*>& nodes , unordered_map<string, Edge*>& edges , bool isShortest = 1);

		Path constructPath();
	};

}
#endif