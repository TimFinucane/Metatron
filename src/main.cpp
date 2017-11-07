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
    compiler.parseFile( "Sentence -> NounPhrase Verb" );
    compiler.parseFile( "Sentence -> NounPhrase Verb NounPhrase" );
    compiler.parseFile( "NounPhrase -> Article AdjectiveSequence Noun(0/has_article)" );
    compiler.parseFile( "NounPhrase -> AdjectiveSequence Noun" );
    compiler.parseFile( "NounPhrase -> Noun" );
    compiler.parseFile( "AdjectiveSequence(/adjective) -> Adjective(/adjective) AdjectiveSequence(/adjective, 0/adjective)" );
    compiler.parseFile( "AdjectiveSequence(/adjective) -> Adjective(/adjective)" );

    // Form words from symbols
    Generation::Translator translator( compiler.getMapping() );
    translator.addWord( "Verb",        Generation::Words::verb );
    translator.addWord( "Noun",        Generation::Words::noun );
    translator.addWord( "Adjective",   Generation::Words::adjective );
    translator.addWord( "Article",     Generation::Words::article );

    std::cout << translator.transform( Grammar::generate( compiler.getMapping().symbols().at( "Sentence" ), compiler.getProductions() ) ) << std::endl;
    
    // And silence
    std::cin.get();

    return 0;
}