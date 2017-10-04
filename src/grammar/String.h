#pragma once

#include <list>

#include "Symbol.h"

namespace Grammar
{
    /*
     * A sequence of symbols, along with
     *  the links between them
     */
    struct String
    {
    public:
        String( unsigned int head )
        {
            symbolList.insert( symbolList.begin(), head );
        }

        void    addLink( unsigned int linkType, const Symbol* first, const Symbol* second );
        void    removeLink( Link* link );
        void    removeLink( std::list<Link>::iterator it );
        void    removeLinks( std::list<Link>::iterator begin, std::list<Link>::iterator end )
        {
            for( auto it = begin; it != end; ++it )
                removeLink( it );
        }

        void    addSymbol( std::list<Symbol>::const_iterator it, unsigned int id )
        {
            // Insert it after the given item.
            symbolList.insert( std::next( it ), id );
        }
        template <typename Iterator>
        void    addSymbols( std::list<Symbol>::const_iterator it, Iterator first, Iterator last )
        {
            symbolList.insert( std::next( it ), first, last );
        }
        std::list<Symbol>::const_iterator   removeSymbol( std::list<Symbol>::const_iterator it )
        {
            for( int i = (int)it->links.size() - 1; i >= 0; --i )\
                removeLink( it->links[i] );

            return symbolList.erase( it );
        }

        const std::list<Link>&      links() const
        {
            return linkList;
        }
        const std::list<Symbol>&    symbols() const
        {
            return symbolList;
        }

    private:
        std::list<Symbol>   symbolList;
        std::list<Link>     linkList;
    };
}