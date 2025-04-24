#include "../../Model/Headers/PathConstructor.h"
using namespace Model;

vector<string> Model::PathConstructor::constructPath(int from, int to, const unordered_map<int, int>& parent) const noexcept
{
    vector<string> path;

    while (to != -1) {
		path.push_back(Model::CitiesMapperID::getCityById(to));

		auto it = parent.find(to);
		if (it == parent.end()) {
			break; // No more parents
		}
		to = it->second;
    }
	reverse(path.begin(), path.end());
    return vector<string>();
}
