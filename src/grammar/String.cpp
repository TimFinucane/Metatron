#include "String.h"

#include <algorithm>

using namespace Grammar;

void    String::addLink( unsigned int linkType, const Symbol* first, const Symbol* second )
{
    linkList.push_back( { linkType, const_cast<Symbol*>(first), const_cast<Symbol*>(second) } );
    const_cast<Symbol*>(first)->links.push_back( &linkList.back() );
    const_cast<Symbol*>(second)->links.push_back( &linkList.back() );
}
void    String::removeLink( Link* link )
{
    auto it = std::find_if( linkList.begin(), linkList.end(), [link]( const Link& element ){ return link == &element; } );

    if( it != linkList.end() )
        removeLink( it );
}
void    String::removeLink( std::list<Link>::iterator it )
{
    std::vector<Link*> linkVector = it->first->links;
    linkVector.erase( std::find( linkVector.begin(), linkVector.end(), &*it ) );

    linkVector = it->second->links;
    linkVector.erase( std::find( linkVector.begin(), linkVector.end(), &*it ) );

    linkList.erase( it );
}