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

		static inline void	addLink( LinkType linkType, Symbol& a, Symbol& b )
		{
			a.links.push_back( { linkType, b } );
			b.links.push_back( { linkType, a } );
		}
    public:
        Symbol( unsigned int id )
            : id( id )
        {
        }

		// Removes all links that this symbol is part of
		void	removeAllLinks()
		{
			using std::iter_swap;

			for( auto& linkInf : links )
			{
				auto& linkVector = linkInf.other().links;
				// Swap and pop
				auto it = std::find( linkVector.begin(), linkVector.end(), Symbol::Link{ linkInf.type, *this } );
				iter_swap( it, linkVector.end() - 1 );
				linkVector.pop_back();
			}
			links.clear();
		}

		// Adds a link of given type between this and the other symbol
		inline void	addLink( LinkType linkType, Symbol& other )
		{
			Symbol::addLink( linkType, *this, other );
		}

        SymbolType            id;
        std::vector<Link>   links;
    };
}