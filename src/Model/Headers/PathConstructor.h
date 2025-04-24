#ifndef PATH_CONSTRUCTOR_H
#define PATH_CONSTRUCTOR_H
#include "Globals.h"
#include "CitiesMapperID.h"

namespace Model{
	class PathConstructor {
	public:

		vector<string> constructPath(int from, int to,const unordered_map<int, int>& parent) const noexcept;
	};

}


#endif
