#ifndef PERSON_H
#define PERSON_H

#include <vector>

class Person
{
public:
    Person();
    Person(int lengthRep);
    ~Person();
    void mutate();
    std::vector<int> generateRep(int lengthRep);
    std::vector<int> representation;
    double score;
};

#endif // PERSON_H
