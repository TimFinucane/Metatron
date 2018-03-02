#pragma once

#include <string>
#include <map>

#include "grammar/Symbol.h"

/*
 * A mapping maps from words to ids for symbols and links. It is created by the compiler
 * and helps for creation and debugging purposes. The symbol mapping contains relations such as Noun -> 1,
 * and links contains things like adjective -> 3, where adjective is the link of an Adjective to a Noun
 */
struct Mapping
{
    using SymbolType = Grammar::SymbolType;
    using LinkType = Grammar::LinkType;

public:
    SymbolType  getOrCreateSymbol( const std::string& str )
    {
        auto it = symbolMap.upper_bound( str );
        if( it != symbolMap.begin() && std::prev( it )->first == str )
            return std::prev( it )->second;
        else
        {
            unsigned int index = (unsigned int)symbolMap.size();
            symbolMap.insert( it, { str, index } );
            return index;
        }
    }
    LinkType    getOrCreateLink( const std::string& str )
    {
        auto it = linkMap.upper_bound( str );
        if( it != linkMap.begin() && std::prev( it )->first == str )
            return std::prev( it )->second;
        else
        {
            unsigned int index = (unsigned int)linkMap.size();
            linkMap.insert( it, { str, index } );
            return index;
        }
    }

    SymbolType  symbol( const std::string& str ) const
    {
        return symbolMap.at( str );
    }
    LinkType    link( const std::string& str ) const
    {
        return linkMap.at( str );
    }

    const std::map<std::string, SymbolType>&    symbols() const
    {
        return symbolMap;
    }
    const std::map<std::string, LinkType>&      links() const
    {
        return linkMap;
    }

private:
    std::map<std::string, SymbolType>   symbolMap;
    std::map<std::string, LinkType>     linkMap;
};