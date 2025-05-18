#include "Globals.h"
#include "Path.h"

namespace Model {

	class PathFinder {
	public:
		PathFinder();

		Path findPath(string source, string destination, unordered_map<string, Node*>& nodes,
			unordered_map<string, Edge*>& edges, bool isShortest = 1);
        Path newfindPath(string source, string destination, unordered_map<string, Node*>& nodes,
            unordered_map<string, Edge*>& edges, unordered_map<string, vector<pair<double, string>>> &adj, bool isShortest = 1);
	};

}
