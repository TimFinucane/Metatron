#pragma once

#include <vector>
#include <algorithm>

namespace Grammar
{
    using SymbolType = unsigned int;
    using LinkType = unsigned int;

    /*
     * Output info about a symbol
     */
    struct Symbol
    {
    private:
        friend class Compiler;
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
            LinkType  type;

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
        ~Symbol()
        {
            removeAllLinks();
        }

		/* 
         * Adds a two way link between this symbol and the other symbol,
         * using the given link type
         */
        void	        addLink( LinkType linkType, Symbol& other )
        {
            Symbol::addLink( linkType, *this, other );
        }
        void            removeLink( LinkType linkType )
        {

        }

        /*
         * Removes every link that this symbol has, also destroying the other
         * end of the link in the process
         */
        void	        removeAllLinks()
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

        /*
         * Checks whether a link with the given details exists in the symbol
         */
        bool            checkLink( LinkType linkType ) const
        {
            return std::find_if( 
                links.begin(), 
                links.end(),
                [linkType]( const Link& link ){ return link.type == linkType; }
            ) != links.end();
        }
        bool            checkLink( LinkType linkType, SymbolType other ) const
        {
            return std::find_if(
                links.begin(),
                links.end(),
                [=]( const Link& link ){ return link.type == linkType && link.other().id == other; }
            ) != links.end();
        }

        /*
         * Gets the number of links with the given details that the symbol is part of
         */
        unsigned int    countLinks( LinkType linkType ) const
        {
            unsigned int count = 0;
            for( const auto& link : links )
                count += (link.type == linkType);

            return count;
        }
        unsigned int    countLinks( LinkType linkType, SymbolType other ) const
        {
            unsigned int count = 0;
            for( const auto& link : links )
                count += (link.type == linkType) && link.other().id == other;

            return count;
        }

        const SymbolType    id;
    private:
        std::vector<Link>   links;
    };
}