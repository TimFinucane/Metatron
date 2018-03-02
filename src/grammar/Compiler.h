#pragma once

#include <map>
#include <string>
#include <istream>
#include <fstream>
#include <random>
#include <list>

#include "Mapping.h"
#include "Production.h"

namespace Grammar
{
	// Chooses a random item from an iterator range, where the first iterator may be chosen but not the last
	template <typename Random, typename Iterator>
	Iterator	chooseFromRange( std::pair<Iterator, Iterator> range, Random& engine )
	{
		std::uniform_int<> uniform( 0, (int)std::distance( range.first, range.second ) - 1 );
		return std::next( range.first, uniform( engine ) );
	}

    class Compiler
    {
    public:
        /*
         * Reads a file, places found productions into the Former, and outputs a map of
         * symbol ids vs their name.
         */
        void    parse( const std::string& file );

        /*
         * Reads a single rule and converts it into a production
         */
        void    parseRule( const std::string& head, const std::string& rule );

        // Members
        const Mapping&  getMapping() const
        {
            return this->mapping;
        }
        const std::multimap<SymbolType, Production>& getProductions() const
        {
            return this->productions;
        }

		// TODO: Add relative chances on each production
		// Generates a series of terminal 'Word classes' from a starting symbol
		template <typename Random>
		std::list<Symbol>	generate( std::string headName, Random& random ) const
		{
			SymbolType head = mapping.symbols().at( headName );

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

				const auto& production = chooseFromRange( productionRange, random )->second;

				// Now apply the production

				// Add symbols
				string.insert( std::next( symbolIt ), production.symbols.begin(), production.symbols.end() );

				// Add internal links
				for( const Production::InternalLink& linkInfo : production.internalLinks )
				{
					Symbol& us = *std::next( symbolIt, linkInfo.thisIndex + 1 );
					Symbol& them = *std::next( symbolIt, linkInfo.otherIndex + 1 );

					Symbol::addLink( linkInfo.type, us, them );
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

							Symbol::addLink( externalLinkInfo.newType, us, them );
						}
					}
				}

				// Now delete old symbol and continue
				symbolIt = string.erase( symbolIt );
			}

			return string;
		}
		std::list<Symbol>	generate( std::string headName ) const
		{
			std::default_random_engine engine{ std::random_device{}() }; // Use a completely random engine
			return generate( headName, engine );
		}

		std::list<Symbol>	operator()( std::string head ) const
		{
			return generate( head );
		}

    private:
        Mapping mapping;
        std::multimap<SymbolType, Production>   productions;
    };

    /*
     * A compilation exception occurs when bad input was passed in.
     */
    class CompilationException : public std::runtime_error
    {
    public:
        explicit CompilationException( Compiler& compiler, const std::string& message )
            : std::runtime_error( "Error trying to read line: " + message ), compiler( compiler )
        {
        }

        Compiler& compiler;
    };
}