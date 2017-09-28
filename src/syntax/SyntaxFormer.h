#pragma once

#include <vector>
#include <list>
#include <map>

namespace Syntax
{
    struct Production
    {
        struct Argument
        {
            // Whether the arg is absolute or relative to the
            //  argument of the production that made it
            bool            absolute;
            unsigned char   headArg; // If relative, the headArg it is based on
            short           value;
        };

        friend class Former;
    public:
        // A bunch of arguments for a single symbol
        using SymbolArgs = std::vector<std::pair<unsigned int, Argument>>;

        void    add( unsigned int symbol, SymbolArgs&& arguments )
        {
            symbols.push_back( { symbol, std::move( arguments ) } );
        }

    private:
        // A bunch of symbols with arguments
        std::vector<std::pair<unsigned int, SymbolArgs>>    symbols;
    };

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