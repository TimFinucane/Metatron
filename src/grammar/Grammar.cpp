#include "Grammar.h"

#include <random>
#include <chrono>

using namespace Grammar;

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
                for( const auto linkInf : symbolIt->links )
                {
                    if( linkInf.type == externalLinkInfo.originalType )
                    {
                        Symbol* us = &*std::next( symbolIt, externalLinkInfo.thisIndex + 1 );
                        Symbol* them = linkInf.other;

                        addLink( externalLinkInfo.newType, us, them );
                    }
                }
            }

            // Now delete old symbol and continue
            // Remove link references
            for( auto linkInf : symbolIt->links )
            {
                auto& otherLinks = linkInf.other->links;
                otherLinks.erase( std::find( otherLinks.begin(), otherLinks.end(), Symbol::Link{ linkInf.type, &*symbolIt } ) );
            }

            symbolIt = string.erase( symbolIt );
        }
        else
        {
            symbolIt++;
        }
    }

    return string;
}