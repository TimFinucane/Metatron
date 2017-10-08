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
    Grammar::Former former;

    Grammar::Reader reader( former );

    reader.read( "Sentence -> NounPhrase Verb" );
    reader.read( "Sentence -> NounPhrase Verb NounPhrase" );
    reader.read( "NounPhrase -> Article AdjectiveSequence Noun(0/has_article)" );
    reader.read( "NounPhrase -> AdjectiveSequence Noun" );
    reader.read( "NounPhrase -> Noun" );
    reader.read( "AdjectiveSequence -> Adjective AdjectiveSequence" );
    reader.read( "AdjectiveSequence -> Adjective" );

    Grammar::String output = former.generate( reader.mapping.symbols["Sentence"] );

    // Form words from symbols
    /*Generation::Translator translator;
    translator.addWord( reader.symbol( "Verb" ),        Generation::Words::Verb() );
    translator.addWord( reader.symbol( "Noun" ),        Generation::Words::Noun() );
    translator.addWord( reader.symbol( "Adjective" ),   Generation::Words::Adjective() );
    translator.addWord( reader.symbol( "Article" ),     Generation::Words::Article() );

    std::cout << translator.transform( output ) << std::endl;*/
    
    // And silence
    char c;
    std::cin >> c;

    return 0;
}