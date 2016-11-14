#pragma once

#include <random>
#include "RandomGenerator.h"

class Random : public RandomGenerator
{
public:
    Random( unsigned int seed );

    unsigned int    generateInteger( unsigned int count );
    double          generateNumber( double max );
private:
    std::mt19937 engine;
};