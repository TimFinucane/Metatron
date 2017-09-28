#include "SyntaxFormer.h"

#include <random>

static std::default_random_engine engine;

// Generates a series of terminals from a starting symbol
std::list<SyntaxFormer::OutSymbol>  SyntaxFormer::generate( unsigned int symbol )
{
    std::list<OutSymbol>  output{ { symbol, std::vector<unsigned int>( symbols[symbol].argumentCount, 0 ) } };

    // Will only exit once no more symbols have been converted
    auto outputIt = output.begin();
    while( outputIt != output.end() )
    {
        if( !symbols[outputIt->symbol].terminal )
        {
            // Choose a random production. TODO: Allow input chances?
            auto prodsPair = productions.equal_range( outputIt->symbol );
            std::uniform_int<> uniform( 0, (int)std::distance( prodsPair.first, prodsPair.second ) );
            auto chosen = std::next( prodsPair.first, uniform( engine ) );
            
            // Add all the production's symbols
            for( auto symbol : chosen->second.symbols )
            {
                std::vector<unsigned int> symbolArgs( symbols[symbol.first].argumentCount, 0 );

                for( auto arg : symbol.second )
                {
                    if( arg.second.absolute )
                        symbolArgs[arg.first] = arg.second.value;
                    else
                        symbolArgs[arg.first] = arg.second.value + outputIt->args[arg.second.headArg];
                }

                output.insert( outputIt, OutSymbol{ symbol.first, symbolArgs } );
            }

            // Erase, and restart loop
            output.erase( outputIt );
            outputIt = output.begin();
            break;
        }
        
        outputIt++;
    }

    return output;
}