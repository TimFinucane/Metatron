#pragma once

#include <vector>

namespace Grammar
{
    struct Symbol;

    /*
     * A Link joins two symbols together, with a linkType defines
     *  to the user why they are joined together.
     */
    struct Link
    {
        // A generic type that allows you to say what kind of link
        unsigned int type;

        // The two symbols the link exists between
        Symbol* first;
        Symbol* second;

        Symbol*& getOther( const Symbol* item )
        {
            return first == item ? second : first;
        }
        Symbol*& getThis( const Symbol* item )
        {
            return first == item ? first : second;
        }
    };

    /*
     * Final output info about a symbol
     */
    struct Symbol
    {
        Symbol( unsigned int id )
            : id( id )
        {
        }

        unsigned int        id;

        // These links will exist as long as the Grammar::Former has not been refreshed
        std::vector<Link*>  links;
    };
}