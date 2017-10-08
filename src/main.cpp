#include <iostream>
#include <string>

#include "grammar/Grammar.h"
#include "generation/Generation.h"

#include "grammar/Reader.h"

#include "generation/words/Noun.h"
#include "generation/words/Verb.h"
#include "generation/words/Adjective.h"
#include "generation/words/Article.h"

int main( int argc, char* argv[] )
{
    Mapping mapping;

    Grammar::Former former;

    Grammar::Reader reader( former, mapping );

    reader.read( "Sentence -> NounPhrase Verb" );
    reader.read( "Sentence -> NounPhrase Verb NounPhrase" );
    reader.read( "NounPhrase -> Article AdjectiveSequence Noun(0/has_article)" );
    reader.read( "NounPhrase -> AdjectiveSequence Noun" );
    reader.read( "NounPhrase -> Noun" );
    reader.read( "AdjectiveSequence -> Adjective AdjectiveSequence" );
    reader.read( "AdjectiveSequence -> Adjective" );

    Grammar::String output = former.generate( mapping.symbols["Sentence"] );

    // Form words from symbols
    Generation::Translator translator( mapping );
    translator.addWord( "Verb",        Generation::Words::Verb() );
    translator.addWord( "Noun",        Generation::Words::Noun() );
    translator.addWord( "Adjective",   Generation::Words::Adjective() );
    translator.addWord( "Article",     Generation::Words::Article() );

    std::cout << translator.transform( output ) << std::endl;
    
    // And silence
    char c;
    std::cin >> c;

    return 0;
}