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
        Production( std::vector<SymbolType>&& symbols )
            : symbols( std::move( symbols ) )
        {
        }

        std::vector<SymbolType>     symbols;
        std::vector<InternalLink>   internalLinks;
        std::vector<ExternalLink>   externalLinks;
    };
}
