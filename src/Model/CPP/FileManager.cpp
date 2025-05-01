#include "../Headers/Globals.h"
namespace Model {
	class FileManager {
	public:
		static void saveToFile(const vector<string>& fileContent, const std::string& filePath) {
			ofstream file(filePath, ios::out | ios::trunc);
			if (file.is_open()) {
				for (const auto& line : fileContent) {
					file << line << endl;
				}
				file.close();
			}
			else {
				cout << "Unable to open file for writing: " << filePath << endl;
			}
		}
		static vector<string> readFromFile(const std::string& filePath) {
			ifstream file(filePath);
			vector<string> lines;
			if (file.is_open()) {
				string line;
				while (getline(file, line)) {
					lines.push_back(line);
				}
				file.close();
			}
			else {
				cout << "Unable to open file for reading: " << filePath << endl;
			}
			return lines;
		}
	};
}