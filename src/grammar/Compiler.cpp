#include "Compiler.h"

#include <regex>

using namespace Grammar;

using Tantrum = std::runtime_error;

void Compiler::parse( const std::string& file )
{
    // Reads a line into the head and the symbols of the production. Currently, productions may not go over one line
    std::regex line( R"(\s*(.*?)\s*->\s*(.*))" );

    auto iterator = file.begin();
    
    while( iterator < file.end() )
    {
        std::smatch results;
        std::regex_search( iterator, file.end(), results, line, std::regex_constants::match_continuous );

        if( results.empty() )
            throw new CompilationException( *this, std::string( iterator, file.end() ) );

        parseRule( results[1].str(), results[2].str() );

        iterator += results.length();
    }
}

void Compiler::parseRule( const std::string& head, const std::string& rule )
{
    // Matches the text, potentially followed by brackets containing more text (the args), followed by plain old whitespace
    // Example: SYMBOLA(2/1024, 3/3)
    std::regex symbol( R"((\w*)(?:\(([^\)]*)\))?\s*)" );

    // Matches a single arg in an arg string
    // Example: 2/1024,
    std::regex arg( R"(\s*(\d*)\/(\w*)(?:\/(\w*))?\s*[,\)]?)" );

    Production production;

    auto iterator = rule.begin();
    do {
        std::smatch results;
        std::regex_search( iterator, rule.end(), results, symbol, std::regex_constants::match_continuous );

        if( results.empty() )
            throw new CompilationException( *this, std::string(iterator, rule.end()) );

        production.symbols.push_back( mapping.getOrCreateSymbol( results[1].str() ) );

        // Go through links
        unsigned int thisIndex = (unsigned int)production.symbols.size() - 1;

        const std::string args = results[2].str();
        auto argIt = args.begin();

        while( argIt < args.end() )
        {
            std::smatch argResults;
            std::regex_search( argIt, args.end(), argResults, arg, std::regex_constants::match_continuous );
            argIt += argResults.length();

            if( argResults[1].compare( "" ) ) // Internal
            {
                unsigned int otherIndex = std::stoi( argResults[1].str() );
                unsigned int linkType = mapping.getOrCreateLink( argResults[2].str() );

                production.internalLinks.push_back( { linkType, thisIndex, otherIndex } );
            }
            else // External
            {
                unsigned int newType = mapping.getOrCreateLink( argResults[2].str() );
                unsigned int originalType = 0;

                // If there are three items, then that means a transfer of one 'type' to another
                if( argResults[3].matched )
                    originalType = mapping.getOrCreateLink( argResults[3].str() );
                else
                    originalType = newType;

                production.externalLinks.push_back( { originalType, newType, thisIndex } );
            }
        }

        iterator += results.length();
    } while( iterator < rule.end() );

    // Read head
    std::smatch results;
    std::regex_search( head, results, symbol, std::regex_constants::match_continuous );

    if( results.empty() )
        throw new CompilationException( *this, head );

    productions.insert( { mapping.getOrCreateSymbol( results[1].str() ), production } );
}