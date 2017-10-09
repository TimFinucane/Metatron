#pragma once

#include <map>
#include <list>

#include "Production.h"

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
        std::list<Symbol>   generate( unsigned int symbol );
    private:
        std::multimap<unsigned int, Production>     productions;
    };
}