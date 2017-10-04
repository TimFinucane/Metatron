#pragma once

#include <vector>
#include <list>
#include <map>

#include "Production.h"
#include "String.h"

namespace Grammar
{
    // The Syntax is the constructor of a sentence/form....=
    // TODO: Add relative chances on each production
    class Former
    {
    public:
        void    addProduction( unsigned int head, Production&& production )
        {
            productions.insert( { head, std::move( production ) } );
        }

        // Generates a series of terminals from a starting symbol
        String  generate( unsigned int symbol );
    private:
        std::multimap<unsigned int, Production>     productions;
    };
}