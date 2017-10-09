#include "Reader.h"

#include <regex>

using namespace Grammar;

using Tantrum = std::runtime_error;

void            Reader::read( const std::string& file )
{
    // Sentence -> NounPhrase(4->)

    // HEAD -> SYMBOLA(2/1024, 3/3) SYMBOLB SYMBOLC(2/3, 1/4)
    // HEADWITHSYMBOL(/3)

    std::regex symbol( R"(\s*(\w*)(?:\(([^\)]*)\))?\s*(->)?)" );
    std::regex arg( R"(\s*(\d*)\/(\w*)(?:\/(\w*))?\s*,?)" );

    auto iterator = file.begin();

    // Create production storage info
    unsigned int head;
    Production production;
    
    while( iterator < file.end() )
    {
        std::smatch results;
        std::regex_search( iterator, file.end(), results, symbol, std::regex_constants::match_continuous );

        iterator += results.length();

        // If there is an arrow, we are at a head and can push back previous symbol
        if( results[3].compare( "->" ) == 0 )
        {
            if( production.size() > 0 )
            {
                former.addProduction( head, std::move( production ) );
                production = Production();
            }

            // Replace head
            head = getSymbol( results[1].str() );

            // TODO: And here we would process the external link requirements
        }
        else // Add a symbol
        {
            production.addSymbol( getSymbol( results[1].str() ) );

            // Go through links
            if( results[2].matched )
            {
                unsigned int thisIndex = (unsigned int)production.size() - 1;

                const std::string args = results[2].str();

                auto argIt = args.begin();
                while( argIt < args.end() )
                {
                    std::regex_search( argIt, args.end(), results, arg, std::regex_constants::match_continuous );
                    argIt += results.length();

                    if( results[1].compare("") ) // Internal
                    {
                        unsigned int otherIndex = std::stoi( results[1].str() );
                        unsigned int linkType = getLink( results[2].str() );

                        production.addInternalLink( { linkType, thisIndex, otherIndex } );
                    }
                    else // External
                    {
                        unsigned int newType = getLink( results[2].str() );
                        unsigned int originalType = 0;

                        if( results[3].matched )
                            originalType = getLink( results[3].str() );
                        else
                            originalType = newType;

                        production.addExternalLink( { originalType, newType, thisIndex } );
                    }
                }
            }
        }
    }

    if( production.size() > 0 )
    {
        former.addProduction( head, std::move( production ) );
        production = Production();
    }
}
unsigned int    Reader::getSymbol( const std::string& name )
{
    auto it = mapping.symbols.upper_bound( name );
    if( it != mapping.symbols.begin() && std::prev( it )->first == name )
        return std::prev( it )->second;
    else
    {
        unsigned int index = (unsigned int)mapping.symbols.size();

        mapping.symbols.insert( it, { name, index } );
        return index;
    }
}
unsigned int    Reader::getLink( const std::string& name )
{
    auto it = mapping.links.upper_bound( name );
    if( it != mapping.links.begin() && std::prev( it )->first == name )
        return std::prev( it )->second;
    else
    {
        unsigned int index = (unsigned int)mapping.links.size();

        mapping.links.insert( it, { name, index } );
        return index;
    }
}