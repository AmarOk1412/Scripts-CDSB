#include "Person.h"

#include <algorithm>
#include <random>

Person::Person()
{
    score = 0;
}

Person::Person(int lengthRep)
{
    representation = generateRep(lengthRep);
    score = 0;
}

Person::~Person()
{

}

std::vector<int> Person::generateRep(int lengthRep)
{
    std::vector<int> ind;

    for(auto i = 0; i < lengthRep; ++i)
        ind.push_back(i);

    std::random_shuffle(&ind[0], &ind[lengthRep]);

    return ind;
}

void Person::mutate()
{
    std::default_random_engine r((unsigned int)time(0));
    auto a = r()%representation.size()+1;
    auto b = r()%representation.size()+1;
    auto temp = representation[a];
    representation[a] = representation[b];
    representation[b] = temp;
}
