#ifndef TOOLS_H
#define TOOLS_H
#include "../Model/Headers/Globals.h"

class Tools {
public:
	static bool isContainSpaces(const string &str) noexcept;
	static bool isSpecialChar(char c);
};

#endif
