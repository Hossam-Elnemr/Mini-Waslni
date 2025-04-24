#include "../Headers/CitiesMapperID.h"
//#include "../Headers/Globals.h"
using namespace Model;
map<string, int> CitiesMapperID::cityToIdx;
map<int, string> CitiesMapperID::idxToCity;

string CitiesMapperID::getCityById(int id)  noexcept(false) {
	string cityName = "Not Founded";
	try {
		cityName = idxToCity.at(id);
	}
	catch (out_of_range &e) {
		cout << e.what() << flush;
	}catch (...) {
		cout << "Unknown error In {CitiesMapperID::getCityById}" << flush;
	}

	return cityName;
}

int CitiesMapperID::getIdByCity(string city)  noexcept(false) {
	int id = -1;
	try {
		id = cityToIdx.at(city);
	}
	catch (out_of_range& e) {
		cout << e.what() << flush;
	}
	catch (...) {
		cout << "Unknown error In {CitiesMapperID::getIdByCity}" << flush;
	}

	return id;
}

void Model::CitiesMapperID::mapCity(string city)
{
	int id = unusedIdx.empty() ? idxToCity.size() : *unusedIdx.begin();
	cityToIdx[city] = id;
	idxToCity[id] = city;	
}

int CitiesMapperID::getCurrentEmptyIdx() {
	//Get the first element in the set or if the set if empty => return the size of the map
	return unusedIdx.empty() ? idxToCity.size() : *unusedIdx.begin();
}

void CitiesMapperID::deleteCity(string city) {
	//Delete the city from two maps
	//Add the id to the set
	int id = cityToIdx[city];
	cityToIdx.erase(city);
	idxToCity.erase(id);
	unusedIdx.insert(id);
}

CitiesMapperID& Model::CitiesMapperID::getInstance()
{
	static CitiesMapperID instance;
	return instance;
}


