#include "Formation.h"
#include "Language.h"

#include <algorithm>

using namespace Syntax;

AdjectiveWord   AdjectiveWord::construct( RandomGenerator* generator, bool plural )
{
    unsigned int num = generator->generateInteger( 4 );

    AdjectiveWord word;
    
    switch( num )
    {
    case 0:
        word.type = Type::DESCRIPTIVE;
        word.degree = static_cast<Degree>(generator->generateInteger( 3 ));
        break;
    case 1:
        word.type = Type::QUANTITATIVE;
        if( plural )
            word.amount = generator->generateInteger( 8 ) + 2;
        else
            word.amount = 1;
        break;
    case 2:
        word.type = Type::DEMONSTRATIVE;
        word.plural = plural;
        break;
    case 3:
        word.type = Type::POSSESSIVE;
        word.possessiveNoun = std::make_unique<NounPhrase>(NounPhrase::construct( generator ));
        break;
    }

    return word;
}

NounPhrase      NounPhrase::construct( RandomGenerator* generator )
{
    NounPhrase noun;

    noun.plural = generator->generateInteger( 2 ) == 1;

    bool hasPossessive = false;
    bool hasQuantitative = false;
    bool hasDemonstrative = false;
    bool hasDescriptive = false;

    while( generator->generateInteger( 100 ) > 50 )
    {
        AdjectivePhrase phrase = AdjectivePhrase::construct( generator, noun.plural );

        if( phrase.word.type == AdjectiveWord::Type::POSSESSIVE && !hasPossessive )
        {
            hasPossessive = true;
            noun.adjectivePhrases.push_back( std::move( phrase ) );
        }
        else if( phrase.word.type == AdjectiveWord::Type::QUANTITATIVE && !hasQuantitative )
        {
            hasQuantitative = true;
            noun.adjectivePhrases.push_back( std::move( phrase ) );
        }
        else if( phrase.word.type == AdjectiveWord::Type::DEMONSTRATIVE && !hasDemonstrative )
        {
            hasDemonstrative = true;
            noun.adjectivePhrases.push_back( std::move( phrase ) );
        }
        else if( phrase.word.type == AdjectiveWord::Type::DESCRIPTIVE )
        {
            hasDescriptive = true;
            noun.adjectivePhrases.push_back( std::move( phrase ) );
        }
    }

    if( hasPossessive || hasDemonstrative )
        noun.premodifier = Premodifier::NONE;
    else if( hasQuantitative || noun.plural )
        noun.premodifier = (Premodifier)generator->generateInteger( 2 );
    else if( hasDescriptive )
        noun.premodifier = (Premodifier)(generator->generateInteger( 2 ) + 1);
    else
        noun.premodifier = (Premodifier)generator->generateInteger( 3 );

    std::sort( noun.adjectivePhrases.begin(), noun.adjectivePhrases.end(), []( const AdjectivePhrase& a, const AdjectivePhrase& b ){ return a.word.type < b.word.type; } );

    return noun;
}

Verb            Verb::construct( RandomGenerator* generator, bool plural, Person person )
{
    Verb verb;

    verb.negative = generator->generateInteger( 2 ) == 1;
    verb.transitive = generator->generateInteger( 100 ) < 70;

    verb.active = (generator->generateInteger( 100 ) > 30) || verb.transitive;

    verb.conjugation = (Conjugation)generator->generateInteger( 6 );

    verb.subjunctive = (generator->generateInteger( 100 ) < 30) && (verb.conjugation != Conjugation::FUTURE || verb.conjugation != Conjugation::FUTURE_PERFECT);

    verb.plural = plural;
    verb.person = person;

    verb.dynamic = generator->generateInteger( 100 ) < 30;

    verb.conjugation = (Conjugation)generator->generateInteger( 6 );

    return verb;
}