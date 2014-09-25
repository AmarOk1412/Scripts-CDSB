#ifndef INTERFACE_H
#define INTERFACE_H

#include "Map.h"
#include "Population.h"

class Interface
{
public:
    Interface();
    ~Interface();

private:
    Population *pop;
    Map *map;
};

#endif // INTERFACE_H
