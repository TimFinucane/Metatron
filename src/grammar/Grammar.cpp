#include "Grammar.h"

#include <random>
#include <chrono>

using namespace Grammar;

// Chooses a random item from an iterator range, where the first iterator may be chosen but not the last
template <typename Iterator>
Iterator    chooseFromRange( std::pair<Iterator, Iterator> range )
{
    static std::default_random_engine engine( (int)std::chrono::high_resolution_clock::now().time_since_epoch().count() );

    std::uniform_int<> uniform( 0, (int)std::distance( range.first, range.second ) - 1 );

    return std::next( range.first, uniform( engine ) );
}

void        addLink( unsigned int linkType, Symbol* a, Symbol* b )
{
    a->links.push_back( { linkType, b } );
    b->links.push_back( { linkType, a } );
}

// Generates a series of terminals from a starting symbol
std::list<Symbol>   Former::generate( unsigned int head )
{
    std::list<Symbol>  string{ Symbol( head ) };

    // Will only exit once no more symbols have been converted
    auto symbolIt = string.begin();
    while( symbolIt != string.end() )
    {
        // Choose a random production. TODO: Allow input chances?
        auto productionRange = productions.equal_range( symbolIt->id );

        // Skip if no productions
        if( productionRange.first != productionRange.second )
        {
            const auto& production = chooseFromRange( productionRange )->second;

            // Now apply the production

            // Add symbols
            string.insert( std::next( symbolIt ), production.symbols.begin(), production.symbols.end() );

            // Add internal links
            for( const Production::InternalLink& linkInfo : production.internalLinks )
            {
                Symbol* us = &*std::next( symbolIt, linkInfo.thisIndex + 1 );
                Symbol* them = &*std::next( symbolIt, linkInfo.otherIndex + 1 );

                addLink( linkInfo.type, us, them );
            }

            // Add external links
            for( const Production::ExternalLink& externalLinkInfo : production.externalLinks )
            {
                // For every link that 
                for( const auto linkInf : symbolIt->links )
                {
                    if( linkInf.type == externalLinkInfo.originalType )
                    {
                        Symbol* us = &*std::next( symbolIt, externalLinkInfo.thisIndex + 1 );
                        Symbol* them = linkInf.other;

                        us->links.push_back( { externalLinkInfo.newType, them } );
                        auto replaceLink = std::find( them->links.begin(), them->links.end(), Symbol::Link{ externalLinkInfo.originalType, &*symbolIt } );
                        replaceLink->type = externalLinkInfo.newType;
                        replaceLink->other = us;
                    }
                }
            }

            // Now delete old symbol and continue
            symbolIt = string.erase( symbolIt );
        }
        else
        {
            symbolIt++;
        }
    }

    return string;
}