#ifndef POPULATION_H
#define POPULATION_H

#include "Person.h"
#include "coord.h"


class Population
{
public:
    Population(int nbPerson, int nbCity);
    ~Population();
    void newGeneration();
    void mutate(int luck);
    void calcScore(std::vector<Coord> cities);
    Person getBestScore();

private:
    void score(Person &ind, std::vector<Coord> cities);
    Person crossOver(Person ind1, Person ind2);
    std::vector<Person> pop;

};

#endif // POPULATION_H
