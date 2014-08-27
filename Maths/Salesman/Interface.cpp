#include "Interface.h"
#include <iostream>
#include <string>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


Interface::Interface()
{
    int nbCity = 0, mapSize = 0, nbGen = 0;
    std::cout << "Travelling Salesman problem resolver" << std::endl;
    std::cout << "Number of cities ? ";
    std::cin >> nbCity;
    std::cout << "Map size ? ";
    std::cin >> mapSize;
    std::cout << "Generation ? ";
    std::cin >> nbGen;

    std::cout << "Generate a map" << std::endl;
    map = new Map(nbCity, mapSize);
    map->saveMap("Cities.png");
    std::cout << "Map saved (Cities.png)" << std::endl;


    std::cout << "Generate a population" << std::endl;
    pop = new Population(100, nbCity);
    std::cout << "Done !" << std::endl;

    for(int i = 1; i <= nbGen; ++i)
    {
        cv::Mat gen = cv::imread("Cities.png");
        std::cout << "Gen n° " << i << std::endl;

        if(i > 1)
        {
            std::cout << "Mutate pop" << std::endl;
            pop->mutate(10);
        }

        std::cout << "Calc score" << std::endl;
        pop->calcScore(map->getCities());
        std::cout << "Done !" << std::endl;

        std::cout << "Get best ind" << std::endl;
        Person best = pop->getBestScore();
        std::cout << "Done ! Score : " << best.score << std::endl;

        for(auto j = 1; j < best.representation.size(); ++j)
            cv::line(gen,
                     cv::Point(map->getCities()[best.representation[j-1]].x, map->getCities()[best.representation[j-1]].y),
                     cv::Point(map->getCities()[best.representation[j]].x, map->getCities()[best.representation[j]].y),
                     (255, 0, 0),
                     2);


        std::cout << "Save image : gen" << i << ".png" << std::endl;
        cv::imwrite("gen"+ std::to_string(i) +".png", gen);
        std::cout << "Prepare new generation" << std::endl;
        pop->newGeneration();
        pop;
    }
}

Interface::~Interface()
{
    delete map;
}
