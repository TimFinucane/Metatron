#include <iostream>
#include <string>

#include "grammar/Grammar.h"
#include "generation/Generation.h"

#include "grammar/Compiler.h"

#include "generation/words/Noun.h"
#include "generation/words/Verb.h"
#include "generation/words/Adjective.h"
#include "generation/words/Article.h"

int main( int, char*[] )
{
    Grammar::Compiler compiler;
    compiler.parse( "Sentence -> NounPhrase Verb" );
    compiler.parse( "Sentence -> NounPhrase Verb NounPhrase" );
    compiler.parse( "NounPhrase -> Article AdjectiveSequence Noun(0/has_article)" );
    compiler.parse( "NounPhrase -> AdjectiveSequence Noun" );
    compiler.parse( "NounPhrase -> Noun" );
    compiler.parse( "AdjectiveSequence(/adjective) -> Adjective(/adjective) AdjectiveSequence(/adjective, 0/adjective)" );
    compiler.parse( "AdjectiveSequence(/adjective) -> Adjective(/adjective)" );

    // Form words from symbols
    Generation::Translator translator( compiler.getMapping() );
    translator.addWord( "Verb",        Generation::Words::verb );
    translator.addWord( "Noun",        Generation::Words::noun );
    translator.addWord( "Adjective",   Generation::Words::adjective );
    translator.addWord( "Article",     Generation::Words::article );

    std::cout << translator.transform( compiler.generate( "Sentence" ) ) << std::endl;
    
    // And silence
    std::cin.get();

    return 0;
}