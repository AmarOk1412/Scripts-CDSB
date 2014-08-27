#include "Map.h"

#include <random>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Map::Map(int nbCity, int mapSize)
{
    cities = generateCities(nbCity, mapSize);
    m_mapSize = mapSize;
}

Map::~Map()
{

}

std::vector<Coord> Map::generateCities(int nbCity, int mapSize)
{
    std::vector<Coord> cities;
    std::default_random_engine r((unsigned int)time(0));

    for(auto i = 0; i < nbCity; ++i)
    {
        Coord c;
        c.x = r()%mapSize + 1;
        c.y = r()%mapSize + 1;
        cities.push_back(c);
    }

    return cities;
}

void Map::saveMap(std::string filename)
{
    cv::Mat image = cv::Mat::zeros(m_mapSize, m_mapSize, CV_8UC3);
    image.setTo(cv::Scalar(255,255,255));

    for(auto i = 0; i < cities.size(); ++i)
        cv::circle(image, cv::Point(cities.at(i).x, cities.at(i).y), 2, (255, 0, 0));

    cv::imwrite(filename, image);
}
