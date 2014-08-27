#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

#include "coord.h"

class Map
{
public:
    Map(int nbCity, int mapSize);
    ~Map();
    void saveMap(std::string filename);
    std::vector<Coord> getCities() { return cities; }

private:
    std::vector<Coord> generateCities(int nbCity, int mapSize);
    std::vector<Coord> cities;

    int m_mapSize;
};

#endif // MAP_H
