#pragma once

#include <algorithm>
#include <map>

#include <Mapping.h>
#include <grammar/Symbol.h>

namespace Generation
{
    /*
     * Defines helper methods for word generation
     */
    class WordPart
    {
    public:
        WordPart( const Mapping& mapping, const Grammar::Symbol& symbol )
            : mapping( mapping ), symbol( symbol )
        {
        }

        bool            hasLink( const std::string& linkName ) const
        {
            unsigned int linkType = mapping.links.find( linkName )->second;

            return std::find_if( symbol.links.begin(), symbol.links.end(),
                                 [linkType]( const Grammar::Symbol::Link& link ){ return link.type == linkType; }
            ) != symbol.links.end();
        }
        bool            hasLink( const std::string& linkName, const std::string& symbolName ) const
        {
            unsigned int linkType = mapping.links.find( linkName )->second;
            unsigned int symbolType = mapping.symbols.find( symbolName )->second;

            return std::find_if( symbol.links.begin(), symbol.links.end(),
                [&]( const Grammar::Symbol::Link& link )
                {
                    return link.type == linkType && link.other->id == symbolType;
                }
            ) != symbol.links.end();
        }

        unsigned int    linkCount( const std::string& linkName ) const
        {
            unsigned int linkType = mapping.links.find( linkName )->second;

            unsigned int count = 0;
            for( const auto& link : symbol.links )
            {
                count += (link.type == linkType);
            }
        }
        unsigned int    linkCount( const std::string& linkName, const std::string& symbolName ) const
        {
            unsigned int linkType = mapping.links.find( linkName )->second;
            unsigned int symbolType = mapping.symbols.find( symbolName )->second;

            unsigned int count = 0;
            for( const auto& link : symbol.links )
            {
                count += (link.type == linkType && link.other->id == symbolType);
            }
        }

        // May not be needed?
        const Grammar::Symbol*   getLink( const std::string& linkType ) const;
        const Grammar::Symbol*   getLink( const std::string& linkType, const std::string& symbolType ) const;
    
    private:
        const Mapping&          mapping;
        const Grammar::Symbol&  symbol;
    };
}