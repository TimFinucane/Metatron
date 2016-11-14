#include "Words.h"
#include "Language.h"

using namespace Syntax;

void WordList::create( std::istream& file, char endfile )
{
    while( file.peek() != endfile && !file.eof() )
    {
        std::string str;
        std::getline( file, str );

        _words.push_back( str );
    }
}

Words::Words( std::istream& adjectivesStream, std::istream& nounsStream, std::istream& verbsStream )
{
    nouns.create( nounsStream, ':' );
    adjectives.create( adjectivesStream, ':' );
    basicVerbs.create( verbsStream, ':' );
}

std::string Words::generateNoun( RandomGenerator* random, const NounPhrase& noun )
{
    std::string out;

    if( noun.adjectivePhrases.size() && noun.adjectivePhrases[0].word.type == AdjectiveWord::Type::DEMONSTRATIVE )
    {
        out += generateAdjective( random, noun.adjectivePhrases[0] );

        if( noun.premodifier != NounPhrase::Premodifier::NONE )
            out += ", ";
        else
            out += " ";
    }

    switch( noun.premodifier )
    {
    case NounPhrase::Premodifier::DEFINITE:
        out += "the ";
        break;
    case NounPhrase::Premodifier::INDEFINITE:
        out += "a "; // TODO: depends on noun
        break;
    }

    // Already in correct order for adjective descriptions
    for( auto i = noun.adjectivePhrases.begin(); i != noun.adjectivePhrases.end(); ++i )
    {
        if( i->word.type == AdjectiveWord::Type::DEMONSTRATIVE )
            continue;

        out += generateAdjective( random, *i ) + " ";
    }

    // Select a random
    out += nouns.chooseRandom( random );

    if( noun.plural )
    {
        if( out[out.length() - 1] == 's' )
            out += "es";
        else
            out += "s";
    }

    // Change to 'an' if applies
    if( noun.premodifier == NounPhrase::Premodifier::INDEFINITE && Language::isVowel( out[2] ) )
        out.insert( 1, "n" );

    return out;
}

std::string Words::generateAdjective( RandomGenerator* random, const AdjectivePhrase& adjective )
{
    std::string out;
    switch( adjective.word.type )
    {
    case AdjectiveWord::Type::POSSESSIVE:
        out = generateNoun( random, *adjective.word.possessiveNoun );
        if( out[out.length() - 1] == 's' )
            out += "'";
        else
            out += "'s";
        break;
    case AdjectiveWord::Type::DEMONSTRATIVE:
        if( adjective.word.plural )
            out = WordList( { "these", "those", "yonder", "yon", "former" } ).chooseRandom( random );
        else
            out = WordList( { "this", "that", "yonder", "yon", "former" } ).chooseRandom( random );
        break;
    case AdjectiveWord::Type::QUANTITATIVE:
        out = std::to_string( adjective.word.amount );
        break;
    case AdjectiveWord::Type::DESCRIPTIVE:
        // TODO: Make better
        out = adjectives.chooseRandom( random );
        break;
    }

    return out;
}

std::string Words::generateVerb( RandomGenerator* random, const Verb& verb )
{
    std::string out;

    switch( verb.conjugation )
    {
    case Verb::Conjugation::PRESENT:
    {
        if( !verb.active )
        {
            if( verb.subjunctive )
                out = "may be ";
            /*else if( verb.dynamic )
            {
                if( verb.person == Person::FIRST && !verb.plural )
                    out = "am ";
                else if( verb.person == Person::THIRD && !verb.plural )
                    out = "is ";
                else
                    out = "are ";
            }*/
        }
        else
            if( verb.subjunctive )
                out = "may ";

        if( verb.negative )
        {
            if( verb.active && !verb.subjunctive && !verb.dynamic )
            {
                if( verb.person != Person::THIRD || verb.plural )
                    out += "do ";
                else
                    out += "does ";
            }

            out += "not ";
        }

        std::string word = basicVerbs.chooseRandom( random );

        if( verb.dynamic )
            out += appendIng( word );
        else if( !verb.active )
            out += appendEd( word );
        else if( !verb.subjunctive && verb.person == Person::THIRD && !verb.plural && !verb.negative ) // Put s ending (it warns)
        {
            if( word[word.length()-1] == 's' )
                word += "es";
            else
                word += "s";

            out += word;
        }
        
        return out;
        break;
    }
    case Verb::Conjugation::IMPERFECT:
        if( verb.subjunctive )
        {
            if( verb.person == Person::FIRST )
                out = "should ";
            else
                out = "would ";

            if( verb.negative )
                out += "not ";

            if( !verb.active )
                out += "be ";
        }
        else
        {
            if( !verb.active )
            {
                if( !verb.plural && (verb.person != Person::SECOND) )
                    out = "was ";
                else
                    out = "were ";
            }
            if( verb.negative )
                out += "not ";
        }

        if( verb.dynamic )
            out += appendIng( basicVerbs.chooseRandom( random ) );
        else if( !verb.active && !verb.subjunctive )
            out += appendEd( basicVerbs.chooseRandom( random ) );
        else
            out += basicVerbs.chooseRandom( random );

        return out;
        break;
    case Verb::Conjugation::FUTURE:
        // Note, must be indicative
        out = "will ";

        if( verb.negative )
            out += "not ";

        if( verb.

        if( verb.active )
            out += basicVerbs.chooseRandom( random );
        else
        {
            out += "be ";
            out += appendEd( basicVerbs.chooseRandom( random ) );
        }

        return out;
        break;
    case Verb::Conjugation::PERFECT:
        if( verb.subjunctive )
            out = "may ";

        if( !verb.subjunctive && verb.person == Person::THIRD && !verb.plural )
            out = "has ";
        else
            out += "have ";

        if( verb.negative )
            out += "not ";

        if( !verb.active )
            out += "been ";

        out += appendEd( basicVerbs.chooseRandom( random ) );

        return out;
        break;
    case Verb::Conjugation::PLUPERFECT:
        if( verb.subjunctive )
        {
            if( verb.person == Person::FIRST )
                out = "should ";
            else
                out = "would ";

            out += "have ";
        }
        else
            out = "had ";

        if( verb.negative )
            out += "not ";

        if( !verb.active )
            out += "been ";

        out += appendEd( basicVerbs.chooseRandom( random ) );
        
        return out;
        break;
    case Verb::Conjugation::FUTURE_PERFECT:
        if( verb.active && verb.person == Person::FIRST )
            out = "shall ";
        else
            out = "will ";

        if( verb.negative )
            out += "not ";

        out += "have ";

        if( !verb.active )
            out += "been ";

        out += appendEd( basicVerbs.chooseRandom( random ) );

        return out;
        break;
    }

    return out;
}

std::string Words::appendEd( std::string word )
{
    if( word[word.length() - 1] == 'e' )
        word += "d";
    else if( word[word.length() - 1] == 'y' )
    {
        word[word.length() - 1] = 'i';
        word += "ed";
    }
    else
    {
        if( !Language::isVowel( word[word.length() - 3] ) && Language::isVowel( word[word.length() - 2] ) )
            word += word[word.length() - 1]; // Double up on a letter
        word += "ed";
    }

    return word;
}
std::string Words::appendIng( std::string word )
{
    if( Language::isVowel( word[word.length() - 1] ) || word[word.length() - 1] == 'y' )
    {
        word[word.length() - 1] = 'i';
        word += "ng";
    }
    else
        word += "ing";

    return word;
}