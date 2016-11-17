#pragma once

#include <string>
#include <vector>
#include <memory>

#include "WordChooser.h"

namespace Syntax
{
    // TODO: Infinitives for nouns and adjectives
    // TODO: Adverbs
    // TODO: Pronouns in non-possessives
    // TODO: Dynamics in verbs

    struct Noun;
	struct NounPhrase;

    template <typename T>
    using Element = std::unique_ptr<T>;

    struct SyntacticalElement
    {
    public:
        virtual std::string form( RandomGenerator& random, const WordChooser& words ) = 0;
    };

    enum class Person
    {
        FIRST,
        SECOND,
        THIRD
    };

    struct Adjective : public SyntacticalElement
    {
        unsigned int    priority;   // Priority in the sequence
        bool            pre;        // Whether or not it is before the noun
    };
    struct Descriptive : public Adjective
    {
        enum class Degree : unsigned int
        {
            POSITIVE,
            COMPARATIVE,
            SUPERLATIVE
        };
    public:
        std::string form( RandomGenerator& random, const WordChooser& words );

        Degree degree;
    };
    struct Quantitative : public Adjective
    {
        std::string form( RandomGenerator& random, const WordChooser& words );

        unsigned int amount;
    };
	// A possessive adjective is one which adds an owner (such as father's in father's car)
	struct Possessive : public Adjective
	{
		std::string form( RandomGenerator& random, const WordChooser& words );

		Element<NounPhrase>	noun;
	};

    // A complete subject/object
    struct Noun : public SyntacticalElement
    {
        Person  person;
        bool    plural;
    };
    struct Pronoun : public Noun
    {
        std::string form( RandomGenerator& random, const WordChooser& words );
    };
    struct NounWord : public Noun
    {
    public:
        std::string form( RandomGenerator& random, const WordChooser& words );
    };

    struct Verb : public SyntacticalElement
    {
    public:
        enum class Conjugation
        {
            PRESENT,
            IMPERFECT,
            FUTURE,
            PERFECT,
            PLUPERFECT,
            FUTURE_PERFECT
        };

    public:
        std::string form( RandomGenerator& random, const WordChooser& words );

		Noun&			subject;

        Conjugation     conjugation;

        bool            negative; // Has a not
        bool            active; // Switches the subject and object I warned/I was warned.
        bool            subjunctive; // Has a may

        bool            transitive; // Has an object

        bool            dynamic; // The ing ending TODO IMPLEMENT
    };

    struct Adverb : public SyntacticalElement
    {
        // TODO:
    };

    struct NounPhrase : public SyntacticalElement
    {
	public:
		// A premodifier is either an article, a possessive, or a demonstrative
		enum class Premodifier
		{
			NONE,
			DEFINITE,
			INDEFINITE
		};
	public:
        std::string form( RandomGenerator& random, const WordChooser& words );

		bool							demonstrative;
		Premodifier                     premodifier;
		Element<Noun>					noun;
        std::vector<Element<Adjective>>	adjectives;

	private:
		std::string formDemonstrative( RandomGenerator& random );
    };

    // A verb with any number of adverbs attached
    /*struct VerbPhrase
    {
        std::string form( RandomGenerator& random, const WordChooser& words );

        Synt<Verb>                  verb;
        std::vector<Synt<Adverb>>   adverbs;
    };*/
    
    struct IndependentClause : public SyntacticalElement
    {
        std::string form( RandomGenerator& random, const WordChooser& words );

		Element<NounPhrase>	subject;
		Element<Verb>		action;

        // Optional, only if action is transitive
		Element<NounPhrase>	object;
    };
}