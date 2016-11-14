#pragma once

class RandomGenerator abstract
{
public:
    // count is the number of potential values (count of 4 means output could be 0-3)
    virtual unsigned int    generateInteger( unsigned int count ) = 0;
    virtual double          generateNumber( double max ) = 0;
};