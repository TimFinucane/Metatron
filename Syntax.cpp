#include "Syntax.h"
#include "Language.h"

#include <algorithm>

using namespace Syntax;

std::string       Descriptive::form( RandomGenerator& random, const WordChooser& words )
{
    std::string word = words.choose( random, WordChooser::Word::ADJECTIVE );

    switch( degree )
    {
    case Degree::COMPARATIVE:
        if( word.back() == 'y' )
            word.back() = 'i';
        
        word += "er";
        break;
    case Degree::SUPERLATIVE:
        if( word.back() == 'y' )
            word.back() == 'i';
        word += "est";
    }

    return word;
}

std::string Quantitative::form( RandomGenerator& random, const WordChooser& words )
{
    // TODO: Add words for singular, double, etc.
    return std::to_string( amount );
}

std::string Demonstrative::form( RandomGenerator& random, const WordChooser& words )
{
    return "Their";
}