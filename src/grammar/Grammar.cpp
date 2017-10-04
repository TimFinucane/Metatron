#include "Grammar.h"

#include <random>

using namespace Grammar;

// Chooses a random item from an iterator range, where the first iterator may be chosen but not the last
template <typename Iterator>
Iterator    chooseFromRange( std::pair<Iterator, Iterator> range )
{
    static std::default_random_engine engine;

    std::uniform_int<> uniform( 0, (int)std::distance( productionRange.first, productionRange.second ) - 1 );

    return std::next( productionRange.first, uniform( engine ) );
}

// Generates a series of terminals from a starting symbol
String      Former::generate( unsigned int symbol )
{
    String  string;

    // Will only exit once no more symbols have been converted
    auto symbolIt = string.symbols().begin();
    while( symbolIt != string.symbols().end() )
    {
        // Choose a random production. TODO: Allow input chances?
        auto productionRange = productions.equal_range( symbolIt->id );

        // Skip if no productions
        if( productionRange.first != productionRange.second )
        {
            const auto& production = chooseFromRange( productionRange )->second;

            // Now apply the production

            // Add symbols
            string.symbols.insert( symbolIt, production.symbols.begin(), production.symbols.end() );

            // Add internal links
            for( const Production::InternalLink& linkInfo : production.internalLinks )
            {
                const Symbol* first = &*std::next( symbolIt, linkInfo.firstIndex + 1 );
                const Symbol* second = &*std::next( symbolIt, linkInfo.secondIndex + 1 );

                string.addLink( linkInfo.type, first, second );
            }

            // Add external links
            for( const Production::ExternalLink& externalLinkInfo : production.externalLinks )
            {
                // Go through links with current symbol, check if of type.
                // TODO: Can speed up slightly by deleting links on the fly? Unless one link is used multiple times
                for( const auto headLink : symbolIt->links )
                {
                    if( headLink->type == externalLinkInfo.originalType )
                    {
                        const Symbol* first = headLink->getOther( &*symbolIt );
                        const Symbol* second = &*std::next( symbolIt, externalLinkInfo.symbol );

                        string.addLink( externalLinkInfo.newType, first, second );
                    }
                }
            }

            // Now delete old symbol and continue
            symbolIt = string.removeSymbol( symbolIt );
        }
        else
        {
            symbolIt++;
        }
    }

    return string;
}