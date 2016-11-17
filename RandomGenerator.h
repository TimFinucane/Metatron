#pragma once

class RandomGenerator abstract
{
public:
    // count is the number of potential values (count of 4 means output could be 0-3)
    virtual unsigned int    integer( unsigned int count ) = 0;
    virtual double          number( double max ) = 0;

	virtual bool			chance( double chance ) = 0;
};