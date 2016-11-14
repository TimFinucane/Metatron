#include "Random.h"

Random::Random( unsigned int seed )
{
    engine.seed( seed );
}

unsigned int Random::generateInteger( unsigned int max )
{
    std::uniform_int_distribution<unsigned int> dist( 0, max - 1 );

    return dist( engine );
}
double      Random::generateNumber( double max )
{
    std::uniform_real_distribution<double> dist( 0.0, max );

    return dist( engine );
}