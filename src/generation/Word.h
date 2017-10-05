#pragma once

#include <algorithm>
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

    protected:
        virtual std::string produceText() = 0;

        bool            hasLink( unsigned int linkType )
        {
            return std::find_if( symbol->links.begin(), symbol->links.end(),
                          [linkType]( const Grammar::Link& link ){ return link.type == linkType; }
            ) != symbol->links.end();
        }
        bool            hasLink( unsigned int linkType, unsigned int symbolType )
        {
            return std::find_if( symbol->links.begin(), symbol->links.end(),
                [&]( const Grammar::Link& link )
            {
                return link.type == linkType && link.getOther( symbol )->id == symbolType;
            }
            ) != symbol->links.end();
        }

        unsigned int    linkCount( unsigned int linkType )
        {
            unsigned int count = 0;
            for( const auto& link : symbol->links )
            {
                count += (link->type == linkType);
            }
        }
        unsigned int    linkCount( unsigned int linkType, unsigned int symbolType )
        {
            unsigned int count = 0;
            for( const auto& link : symbol->links )
            {
                count += (link->type == linkType && link->getOther( symbol )->id == symbolType);
            }
        }

        // May not be needed?
        const Symbol*   getLink( unsigned int linkType );
        const Symbol*   getLink( unsigned int linkType, unsigned int symbolType );
    
    private:
        const Grammar::Symbol* symbol;
    };
}