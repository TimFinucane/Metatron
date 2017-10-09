#pragma once

#include <vector>

namespace Grammar
{
    /*
     * Output info about a symbol
     */
    struct Symbol
    {
    public:
        /*
         * A Link informs a symbol about another symbol that
         * is in some way related to it.
         */
        struct Link
        {
            // A generic type that allows you to say what kind of link
            unsigned int    type;

            Symbol*         other;

            bool operator==( const Link& link )
            {
                return link.type == type && link.other == other;
            }
        };

    public:
        Symbol( unsigned int id )
            : id( id )
        {
        }

        unsigned int        id;

        // These links will exist as long as the Grammar::Former has not been refreshed
        std::vector<Link>  links;
    };
}