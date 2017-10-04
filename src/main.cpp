#include <iostream>

#include "grammar/Grammar.h"

const unsigned int SENTENCE = 0;
const unsigned int VERB = 1;
const unsigned int ADJECTIVE = 2;
const unsigned int NOUN = 3;
const unsigned int NOUN_PHRASE = 4;
const unsigned int ARTICLE = 5;

int main( int argc, char* argv[] )
{
    Grammar::Former former;

    former.addSymbol( SENTENCE, 0, false );
    former.addSymbol( VERB, 0, true );
    former.addSymbol( ADJECTIVE, 0, true );
    former.addSymbol( NOUN, 0, true );
    former.addSymbol( NOUN_PHRASE, 0, false );
    former.addSymbol( ARTICLE, 0, true );

    Grammar::Production production;
    // Sentence A
    production.add( NOUN_PHRASE, {} );
    production.add( VERB, {} );

    former.addProduction( SENTENCE, std::move( production ) );
    production = Grammar::Production();

    // Sentence B
    production.add( ARTICLE, {} );
    production.add( NOUN_PHRASE, {} );
    production.add( VERB, {} );

    former.addProduction( SENTENCE, std::move( production ) );
    production = Grammar::Production();

    // Noun phrase A
    production.add( ADJECTIVE, {} );
    production.add( NOUN_PHRASE, {} );
    
    former.addProduction( NOUN_PHRASE, std::move( production ) );
    production = Grammar::Production();

    // Noun phrase B
    production.add( NOUN, {} );

    former.addProduction( NOUN_PHRASE, std::move( production ) );
    production = Grammar::Production();

    for( auto symbol : former.generate( SENTENCE ) )
    {
        switch( symbol.symbol )
        {
        case VERB:
            std::cout << "Verb";
            break;
        case ADJECTIVE:
            std::cout << "Adjective";
            break;
        case NOUN:
            std::cout << "Noun";
            break;
        case ARTICLE:
            std::cout << "Article";
            break;
        default:
            std::cout << "Invalid";
            break;
        }

        std::cout << " ";
    }

    std::cout << std::endl;

    char c;
    std::cin >> c;

    return 0;
}