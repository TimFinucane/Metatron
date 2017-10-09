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

    // Form words from symbols
    Generation::Translator translator( mapping );
    translator.addWord( "Verb",        Generation::Words::Verb() );
    translator.addWord( "Noun",        Generation::Words::Noun() );
    translator.addWord( "Adjective",   Generation::Words::Adjective() );
    translator.addWord( "Article",     Generation::Words::Article() );

    std::cout << translator.transform( former.generate( mapping.symbols["Sentence"] ) ) << std::endl;
    
    // And silence
    std::cin.get();

    return 0;
}