#include "Tools.h"


bool Tools::isContainSpaces(const string &str) noexcept {
	for (char c : str)
		if (isspace(c))
			return true;
	return false;
}