#pragma once

#include <vector>
#include <list>
#include <map>

#include "Production.h"

namespace Grammar
{
    // The Syntax is the constructor of a sentence/form.
    // TODO: Add contexts to heads of productions
    // TODO: Add relative chances on each production
    class Former
    {
    public:
        struct OutSymbol
        {
            unsigned int                symbol;
            std::vector<unsigned int>   args;
        };
    public:
        void    addSymbol( unsigned int symbol, unsigned int argumentCount, bool terminal )
        {
            auto& el = symbols[symbol];

            el.argumentCount = argumentCount;
            el.terminal = terminal;
        }

        void    addProduction( unsigned int head, Production&& production )
        {
            // TODO: Confirm symbols exist?

            productions.insert( { head, std::move( production ) } );
        }

        // Generates a series of terminals from a starting symbol
        std::list<OutSymbol>    generate( unsigned int symbol );

    private:
        struct SymbolInfo
        {
            unsigned int    argumentCount;
            bool            terminal; // Whether or not any productions use the symbol
        };

        std::map<unsigned int, SymbolInfo>          symbols;
        std::multimap<unsigned int, Production>     productions;
    };

}