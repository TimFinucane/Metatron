#pragma once

#include <algorithm>
#include <map>

#include <Mapping.h>
#include <grammar/Symbol.h>

namespace Generation
{
    /*
     * Defines a terminal symbol that can generate
     * ouput text.
     */
    class Word
    {
        using Symbol = Grammar::Symbol;
    public:
        virtual ~Word() = default;

        std::string generate( const Grammar::Symbol* symbol )
        {
            this->symbol = symbol;
            return produceText();
        }

        void    map( const Mapping& mapping )
        {
            this->mapping = &mapping;
        }
    protected:
        virtual std::string produceText() = 0;

        bool            hasLink( const std::string& linkName )
        {
            unsigned int linkType = mapping->links.find( linkName )->second;

            return std::find_if( symbol->links.begin(), symbol->links.end(),
                                 [linkType]( const Grammar::Link* link ){ return link->type == linkType; }
            ) != symbol->links.end();
        }
        bool            hasLink( const std::string& linkName, const std::string& symbolName )
        {
            unsigned int linkType = mapping->links.find( linkName )->second;
            unsigned int symbolType = mapping->symbols.find( symbolName )->second;

            return std::find_if( symbol->links.begin(), symbol->links.end(),
                [&]( const Grammar::Link* link )
            {
                return link->type == linkType && link->getOther( symbol )->id == symbolType;
            }
            ) != symbol->links.end();
        }

        unsigned int    linkCount( const std::string& linkName )
        {
            unsigned int linkType = mapping->links.find( linkName )->second;

            unsigned int count = 0;
            for( const auto& link : symbol->links )
            {
                count += (link->type == linkType);
            }
        }
        unsigned int    linkCount( const std::string& linkName, const std::string& symbolName )
        {
            unsigned int linkType = mapping->links.find( linkName )->second;
            unsigned int symbolType = mapping->symbols.find( symbolName )->second;

            unsigned int count = 0;
            for( const auto& link : symbol->links )
            {
                count += (link->type == linkType && link->getOther( symbol )->id == symbolType);
            }
        }

        // May not be needed?
        const Symbol*   getLink( const std::string& linkType );
        const Symbol*   getLink( const std::string& linkType, const std::string& symbolType );
    
    private:
        const Mapping* mapping;

        const Grammar::Symbol* symbol;
    };
}