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
    std::regex arg( R"(\s*(\d*)\/(\d*)\s*,?)" );

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
        if( results.size() == 4 && results[3].compare( "->" ) == 0 )
        {
            if( production.size() > 0 )
            {
                former.addProduction( head, std::move( production ) );
                production = Production();
            }

            // Replace head
            head = getUniqueId( results[1].str() );

            // TODO: And here we would process the external link requirements
        }
        else // Add a symbol
        {
            production.addSymbol( getUniqueId( results[1].str() ) );

            // Go through links
            if( results.size() == 3 && !results[2].str().empty() )
            {
                unsigned int thisIndex = production.size() - 1;

                const std::string args = results[2].str();

                auto argIt = args.begin();
                while( argIt < args.end() )
                {
                    std::regex_match( argIt, args.end(), results, arg, std::regex_constants::match_continuous );

                    unsigned int otherIndex = std::stoi( results[1].str() );
                    unsigned int linkType = std::stoi( results[2].str() );

                    production.addInternalLink( { linkType, thisIndex, otherIndex } );
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
unsigned int    Reader::getUniqueId( const std::string& name )
{
    auto it = symbolNames.upper_bound( name );
    if( it != symbolNames.begin() && std::prev( it )->first == name )
        return std::prev( it )->second;
    else
    {
        unsigned int index = (unsigned int)symbolNames.size();

        symbolNames.insert( it, { name, index } );
        return index;
    }
}