#include <iostream>
#include <string>

#include "grammar/Grammar.h"

enum SymbolType : unsigned int
{
    SENTENCE,
    VERB,
    ADJECTIVE,
    NOUN,
    NOUN_PHRASE,
    ARTICLE,
    ADJECTIVE_SEQUENCE
};

std::map<unsigned int, std::string> names
{
    { VERB, "verb" },
    { ADJECTIVE, "adjective" },
    { NOUN, "noun" },
    { ARTICLE, "article" }
};

int main( int argc, char* argv[] )
{
    using namespace Grammar;

    Former former;

    former.addProduction( SENTENCE, Production( { NOUN_PHRASE, VERB } ) );
    former.addProduction( SENTENCE, Production( { NOUN_PHRASE, VERB, NOUN_PHRASE } ) );
    former.addProduction( NOUN_PHRASE, Production( { ARTICLE, ADJECTIVE_SEQUENCE, NOUN } ) );
    former.addProduction( NOUN_PHRASE, Production( { ADJECTIVE_SEQUENCE, NOUN } ) );
    former.addProduction( NOUN_PHRASE, Production( { NOUN } ) );
    former.addProduction( ADJECTIVE_SEQUENCE, Production( { ADJECTIVE } ) );
    former.addProduction( ADJECTIVE_SEQUENCE, Production( { ADJECTIVE, ADJECTIVE_SEQUENCE } ) );

    String output = former.generate( SENTENCE );

    for( const Symbol& symbol : output.symbols() )
    {
        std::cout << names[symbol.id] << " ";
    }
    std::cout << std::endl;

    char c;
    std::cin >> c;

    return 0;
}