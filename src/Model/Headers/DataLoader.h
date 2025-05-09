#ifndef DataLoader_H
#define DataLoader_H
#include "Globals.h"
#include "../Headers/Manager.h"
#include "../Headers/FileManager.h"

namespace Model {
	class DataLoader {
	public: 
        static void loadGraphsFromFile(const vector<string>& fileContent) ;
	};
}
#endif
