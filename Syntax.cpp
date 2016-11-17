#include "Syntax.h"
#include "Language.h"

#include <algorithm>

using namespace Syntax;

std::string	Descriptive::form( RandomGenerator& random, const WordChooser& words )
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
std::string Possessive::form( RandomGenerator& random, const WordChooser& words )
{
	// TODO:
	return noun->form( random, words ) + "'s";
}

std::string Pronoun::form( RandomGenerator& random, const WordChooser& words )
{
	switch( person )
	{
	case Person::FIRST:
		if( plural )
			return "my";
		else
			return "our";
		break;
	case Person::SECOND:
		return "your";
		break;
	case Person::THIRD:
		if( plural )
			return "their";
		else
		{
			switch( random.integer( 3 ) )
			{
			case 0:
				return "his";
				break;
			case 1:
				return "hers";
				break;
			case 2:
				return "its";
				break;
			}
		}
		break;
	}

	return "ERROR";
}
std::string NounWord::form( RandomGenerator& random, const WordChooser& words )
{
	return words.choose( random, WordChooser::Word::NOUN );
}
std::string Verb::form( RandomGenerator& random, const WordChooser& words )
{
	std::string out;

	switch( conjugation )
	{
	case Conjugation::PERFECT:
	{
		std::string word = words.choose( random, WordChooser::Word::VERB );
		if( subjunctive )
		{
			out += "may ";

			if( negative )
				out += "not ";

			if( !active || dynamic )
				out += "be ";
		}
		else
		{
			if( !active || ( negative && dynamic ) )
			{
				if( subject.plural || subject.person == Person::SECOND )
					out += "are ";
				else if( subject.person == Person::FIRST )
					out += "am ";
				else
					out += "is ";

				if( negative )
					out += "not ";
			}
			else
			{
				if( negative )
					out += "did not ";
			}
		}

		if( dynamic )
			return out + Language::appendIng( word );
		else if( !active )
			return out + Language::appendEd( word );
		else
			return out + word;
	}
	case Conjugation::IMPERFECT:
	{
		// TODO:
	}
	}

	return "ERROR";
}

std::string NounPhrase::form( RandomGenerator& random, const WordChooser& words )
{
	std::string out;
	if( demonstrative )
	{
		out = formDemonstrative( random );

		if( premodifier != Premodifier::NONE )
			out += ",";
	}

	if( premodifier == Premodifier::DEFINITE )
		out += " the";
	else if( premodifier == Premodifier::INDEFINITE )
		out += " a";

	unsigned int i = 0;
	while( adjectives[i]->pre )
	{
		out += " " + adjectives[i]->form( random, words );
		i++;
	}

	out += " " + words.choose( random, WordChooser::Word::NOUN );

	while( i < adjectives.size() )
	{
		out += " " + adjectives[i]->form( random, words );
		i++;
	}

	return out;
}
std::string NounPhrase::formDemonstrative( RandomGenerator& random )
{
	// TODO:
	return "this";
}

std::string IndependentClause::form( RandomGenerator& random, const WordChooser& words )
{
	std::string out = subject->form( random, words ) + " ";
	out += action->form( random, words ) + " ";

	if( action->transitive )
		out += object->form( random, words );

	return out;
}