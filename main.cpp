#include <fstream>
#include <iostream>
#include <time.h>

#include "Sentence.h"
#include "Random.h"
#include "Words.h"

int main( int argc, char* argv[] )
{
    Random random( time( nullptr ) );

    std::fstream nouns( "nouns.txt", std::fstream::in );
    std::fstream verbs( "verbs.txt", std::fstream::in );
    std::fstream adjectives( "adjectives.txt", std::fstream::in );

    std::fstream output( "output.txt", std::fstream::out );

    Syntax::Words words( adjectives, nouns, verbs );

    for( unsigned int i = 0; i < 100; ++i )
    {
        Syntax::IndependentClause sentence( &random );

        std::string out = sentence.construct( &random, &words );

        std::cout << out << std::endl;
        output << out << std::endl;
    }

    char c;
    std::cin >> c;

    return 0;
}