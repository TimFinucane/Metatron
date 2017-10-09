#pragma once

#include <vector>
#include <tuple>

#include "Symbol.h"

namespace Grammar
{
    /*
     * A production defines one possible conversion from a nonterminal symbol
     * to a series of symbols with possible links between them
     */
    struct Production
    {
        friend class Former;

        /*
        * An external link creates a symbol made by a production with
        * the symbol linked to by that production's head.
        */
        struct ExternalLink
        {
            // The link type to find from the original link
            unsigned int originalType;

            // The link type to replace this with
            unsigned int newType;

            // The index to the symbol (from this production) that
            //  the link connects to.
            unsigned int thisIndex;
        };

        /*
        * A link between two items in a production
        */
        struct InternalLink
        {
            unsigned int type;

            unsigned int thisIndex;
            unsigned int otherIndex;
        };
    public:
        Production() {}
        Production( std::vector<unsigned int>&& symbols )
            : symbols( std::move( symbols ) )
        {
        }

        void    addSymbol( unsigned int symbol )
        {
            symbols.push_back( symbol );
        }
        void    addInternalLink( const InternalLink& link )
        {
            internalLinks.push_back( link );
        }
        void    addExternalLink( const ExternalLink& link )
        {
            externalLinks.push_back( link );
        }

        unsigned int    symbol( size_t index )
        {
            return symbols[index];
        }
        size_t          size()
        {
            return symbols.size();
        }

    private:
        std::vector<unsigned int>   symbols;
        std::vector<InternalLink>   internalLinks;
        std::vector<ExternalLink>   externalLinks;
    };
}
