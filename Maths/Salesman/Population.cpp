#include "Population.h"

#include <random>
#include <algorithm>
#include <cstring>

struct Comparator {
  bool operator()(Person a, Person b) {
    return (a.score < b.score );
  }
} comparator;

Population::Population(int nbPerson, int nbCity)
{
    for(auto i = 0; i < nbPerson; ++i)
        pop.push_back(Person(nbCity));
}

Population::~Population()
{

}

Person Population::crossOver(Person ind1, Person ind2)
{
    Person toReturn;

    std::vector<int> newRep;
    std::default_random_engine r((unsigned int)time(0));

    int temp[ind1.representation.size()];
    int present[ind1.representation.size()];
    for(auto i = 0; i < ind1.representation.size(); ++i)
        present[i] = 0;

    auto cut = r()%ind1.representation.size() + 1;

    for(auto i = 0; i < cut; ++i)
        temp[i] = ind1.representation[i];
    for(auto i = cut; i < ind1.representation.size(); ++i)
        temp[i] = ind2.representation[i];

    for(auto i = 0; i < ind1.representation.size(); ++i)
        present[temp[i]] += 1;

    for(auto i = 0; i < ind1.representation.size(); ++i)
    {
        if(present[i] == 0)
        {
            auto j = 0;
            while(j < ind1.representation.size())
            {
                if(present[j] == 2)
                {
                    present[j] = 1;
                    break;
                }
                ++j;
            }


            for(auto k = cut; k < ind1.representation.size(); ++k)
            {
                if(temp[k] == j)
                    temp[k] = i;
            }
        }
    }

    for(auto i = 0; i < ind1.representation.size(); ++i)
        newRep.push_back(temp[i]);

    toReturn.representation = newRep;

    return toReturn;
}

void Population::newGeneration()
{
    std::vector<Person> newPop;
    std::default_random_engine r((unsigned int)time(0));

    sort(pop.begin(), pop.end(), comparator);

    for(auto i = 0; i < pop.size()/2 ; ++i)
        newPop.push_back(pop.at(i));

    for(auto i = 0; i < pop.size()/2 ; ++i)
    {
        auto ind1 = r()%pop.size()/2 + 1;
        auto ind2 = r()%pop.size()/2 + 1;

        newPop.push_back(crossOver(pop.at(ind1), pop.at(ind2)));
    }

    pop.clear();
    pop = newPop;
}

void Population::mutate(int luck)
{
    std::default_random_engine r((unsigned int)time(0));
    for(auto p : pop)
        if(r()%100+1 <= luck)
            p.mutate();
}

void Population::calcScore(std::vector<Coord> cities)
{
    for(auto i = 0; i < pop.size(); ++i)
        score(pop[i], cities);
}

void Population::score(Person &ind, std::vector<Coord> cities)
{
    double score = 0;
    for(auto i = 1; i < ind.representation.size(); ++i)
        score += sqrt(pow(cities[ind.representation[i]].x - cities[ind.representation[i-1]].x, 2) +
                          pow(cities[ind.representation[i]].y - cities[ind.representation[i-1]].y, 2));
    ind.score = score;
}

Person Population::getBestScore()
{

    auto minScore = pop[0].score;
    Person minInd = pop[0];

    for(auto i = 0; i < pop.size(); ++i)if(pop[i].score < minScore)
        {
            minScore = pop[i].score;
            minInd = pop[i];
        }

    return minInd;
}
