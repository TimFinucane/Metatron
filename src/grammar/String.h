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
        void    addLink( unsigned int linkType, const Symbol* first, const Symbol* second )
        {
            linkList.push_back( { linkType, first, second } );
            first->links.push_back( &linkList.back() );
            second->links.push_back( &linkList.back() );
        }
        void    removeLink( Link* link )
        {
            auto it = std::find_if( linkList.begin(), linkList.end(), [link]( const Link& element ){ return link == &element; } );

            if( it != linkList.end() )
                removeLink( it );
        }
        void    removeLink( std::list<Link>::iterator it )
        {
            std::vector<Link*> linkVector = it->first->links;
            linkVector.erase( std::find( linkVector.begin(), linkVector.end(), &*it ) );

            linkVector = it->second->links;
            linkVector.erase( std::find( linkVector.begin(), linkVector.end(), &*it ) );

            linkList.erase( it );
        }
        void    removeLinks( std::list<Link>::iterator begin, std::list<Link>::iterator end )
        {
            for( auto it = begin; it != end; ++it )
            {
                removeLink( it );
            }
        }

        void    addSymbol( std::list<Symbol>::const_iterator it, Symbol& symbol )
        {
            symbolList.insert( it, symbol );
        }
        template <typename Iterator>
        void    addSymbols( std::list<Symbol>::const_iterator it, Iterator first, Iterator last )
        {
            symbolList.insert( it, first, last );
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