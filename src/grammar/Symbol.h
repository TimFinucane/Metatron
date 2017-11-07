#pragma once

#include <vector>

namespace Grammar
{
    using SymbolType = unsigned int;
    using LinkType = unsigned int;

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
            Link( LinkType type, Symbol& symbol )
                : type( type ), _other( &symbol )
            {
            }

            // A generic type that allows you to say what kind of link
            LinkType    type;

            Symbol&         other()
            {
                return *_other;
            }
            const Symbol&   other() const
            {
                return *_other;
            }

            bool operator==( const Link& link )
            {
                return link.type == type && link._other == _other;
            }

        private:
            Symbol*     _other; // Because references aren't reseatable they arent usable in a vector :(
        };

    public:
        Symbol( unsigned int id )
            : id( id )
        {
        }

        SymbolType            id;

        std::vector<Link>   links;
    };
}