#ifndef PathFinder_H
#define PathFinder_H
#include "Globals.h"
#include "../Headers/Path.h"

namespace Model {

	class PathFinder {
	public:
		PathFinder();

		Path findPath(string source, string destination, unordered_map<string, Node*>& nodes,
			unordered_map<string, Edge*>& edges, bool isShortest = 1);
	};

}
#endif