#pragma once

#include <map>
#include <list>
#include <random>

#include "Production.h"

namespace Grammar
{
    namespace details
    {
        // Chooses a random item from an iterator range, where the first iterator may be chosen but not the last
        template <typename Random, typename Iterator>
        Iterator    chooseFromRange( std::pair<Iterator, Iterator> range, Random& engine )
        {
            std::uniform_int<> uniform( 0, (int)std::distance( range.first, range.second ) - 1 );

            return std::next( range.first, uniform( engine ) );
        }

        // Adds a link of given type between the two symbols
        inline void        addLink( LinkType linkType, Symbol& a, Symbol& b )
        {
            a.links.push_back( { linkType, b } );
            b.links.push_back( { linkType, a } );
        }

        // Removes all links that this symbol is part of
        inline void        removeAllLinks( Symbol& symbol )
        {
            using std::iter_swap;

            for( auto& linkInf : symbol.links )
            {
                auto& linkVector = linkInf.other().links;
                // Swap and pop
                auto it = std::find( linkVector.begin(), linkVector.end(), Symbol::Link{ linkInf.type, symbol } );
                iter_swap( it, linkVector.end() - 1 );
                linkVector.pop_back();
            }
            symbol.links.clear();
        }
    }

    // TODO: Add relative chances on each production
    // Generates a series of terminal 'Word classes' from a starting symbol
    template <typename Random>
    std::list<Symbol>   generate( SymbolType head, const std::multimap<SymbolType, Production>& productions, Random& random )
    {
        std::list<Symbol>  string{ Symbol( head ) };

        // Will only exit once no more symbols have been converted
        auto symbolIt = string.begin();
        while( symbolIt != string.end() )
        {
            // Choose a random production. TODO: Allow input chances?
            auto productionRange = productions.equal_range( symbolIt->id );

            // Skip if no productions
            if( productionRange.first == productionRange.second )
            {
                symbolIt++;
                continue;
            }

            const auto& production = details::chooseFromRange( productionRange, random )->second;

            // Now apply the production

            // Add symbols
            string.insert( std::next( symbolIt ), production.symbols.begin(), production.symbols.end() );

            // Add internal links
            for( const Production::InternalLink& linkInfo : production.internalLinks )
            {
                Symbol& us = *std::next( symbolIt, linkInfo.thisIndex + 1 );
                Symbol& them = *std::next( symbolIt, linkInfo.otherIndex + 1 );

                details::addLink( linkInfo.type, us, them );
            }

            // Add external links
            for( const Production::ExternalLink& externalLinkInfo : production.externalLinks )
            {
                for( auto& linkInf : symbolIt->links )
                {
                    if( linkInf.type == externalLinkInfo.originalType )
                    {
                        Symbol& us = *std::next( symbolIt, externalLinkInfo.thisIndex + 1 );
                        Symbol& them = linkInf.other();

                        details::addLink( externalLinkInfo.newType, us, them );
                    }
                }
            }

            // Now delete old symbol and continue
            details::removeAllLinks( *symbolIt );
            symbolIt = string.erase( symbolIt );
        }

        return string;
    }
    inline std::list<Symbol>   generate( SymbolType head, const std::multimap<SymbolType, Production>& productions )
    {
        std::default_random_engine engine{};
        return generate( head, productions, engine );
    }
}