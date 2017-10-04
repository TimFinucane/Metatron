#pragma once

#include <vector>
#include <tuple>

namespace Grammar
{
    struct Link
    {
        // Whether the arg is absolute or relative to the
        //  argument of the production that made it
        bool            absolute;
        unsigned char   headArg; // If relative, the headArg it is based on
        short           value;
    };

    struct Production
    {
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
}
