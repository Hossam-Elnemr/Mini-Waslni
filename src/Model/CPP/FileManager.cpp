#include "../Headers/FileManager.h"
using namespace std;
using namespace Model;
void FileManager::saveToFile(const vector<string>& fileContent, const std::string& filePath) {
	ofstream fout(filePath, ios::out | ios::trunc);
	if (fout.is_open()) {
		for (const auto& line : fileContent) {
			fout << line << endl;
		}
		fout.close();
	}
	else {
		cout << "Unable to open file for writing: " << filePath << endl;
	}
}
vector<string> FileManager::readFromFile(const std::string& filePath) {
	ifstream fin(filePath);
	vector<string> lines;
	if (fin.is_open()) {
		string line;
		while (getline(fin, line)) {
			lines.push_back(line);
		}
		fin.close();
	}
	else {
		cout << "Unable to open file for reading: " << filePath << endl;
	}
	return lines;
}
