#ifndef CITIES_MAPPER_ID_H
#define CITIES_MAPPER_ID_H
#include "Globals.h"
namespace Model {
	class CitiesMapperID {
		static CitiesMapperID instance;
		static map<string, int> cityToIdx;
		static map<int, string> idxToCity;
		static set<int> unusedIdx; //When Delete a city => add the id to this set

		CitiesMapperID();

	public:
		static string getCityById(int id) noexcept(false);
		static int getIdByCity(string city) noexcept(false);
		static void mapCity(string city);
		static int getCurrentEmptyIdx();

		static void deleteCity(string city);

		static CitiesMapperID& getInstance();

		CitiesMapperID(const CitiesMapperID&) = delete;
		CitiesMapperID(const CitiesMapperID&&) = delete;
		//CitiesMapperID& operator=(const CitiesMapperID&) = delete;
		
	};
}
#endif