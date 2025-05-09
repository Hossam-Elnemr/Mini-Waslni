#ifndef FileManager_H
#define FileManager_H
#include "../Headers/Globals.h"
namespace Model {
	class FileManager {
	public:
		static void saveToFile(const vector<string>& fileContent, const std::string& filePath);
		static vector<string> readFromFile(const std::string& filePath);
	};
}
#endif
