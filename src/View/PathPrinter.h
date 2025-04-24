#ifndef PATH_PRINTER_H
#define PATH_PRINTER_H
#include "../Model/Headers/Globals.h"

namespace View{
	class PathPrinter {
	public:

		void printPath(const vector<string>& path, double distance) const noexcept;
	};
}

#endif