#pragma once

#include <string>
#include <vector>
#include <memory>

#include "RandomGenerator.h"

namespace Syntax
{
    // TODO: Infinitives for nouns and adjectives
    // TODO: Adverbs
    // TODO: Pronouns in non-possessives
    // TODO: Dynamics in verbs

    enum class Person
    {
        FIRST,
        SECOND,
        THIRD
    };
    struct NounPhrase;

    //struct AdjectiveClause;
    struct AdjectiveWord
    {
    public:
        enum class Type
        {
            DEMONSTRATIVE,
            POSSESSIVE,
            QUANTITATIVE,
            DESCRIPTIVE
        };
        enum class Degree : unsigned int
        {
            POSITIVE,
            COMPARATIVE,
            SUPERLATIVE
        };
    public:
        static AdjectiveWord    construct( RandomGenerator* generator, bool plural );

        Type                        type;

        // For if the adjective is descriptive
        Degree                      degree;

        // Number to use, for if the adjective is quantitative
        unsigned int                amount;

        // For if the adjective is demonstrative
        bool                        plural;

        // A possessive noun, if the adjective is actually possessive
        std::unique_ptr<NounPhrase> possessiveNoun;
    };
    struct AdjectivePhrase
    {
        static AdjectivePhrase      construct( RandomGenerator* generator, bool plural )
        {
            AdjectivePhrase phrase;
            phrase.word = AdjectiveWord::construct( generator, plural );

            return phrase;
        }

        // TODO: Expand
        // For now, just a word
        AdjectiveWord word;
    };


    // A complete subject/object
    struct NounPhrase
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
        static NounPhrase               construct( RandomGenerator* generator );

        std::vector<AdjectivePhrase>    adjectivePhrases;
        bool                            plural;
        Premodifier                     premodifier;
    };


    struct Verb
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
        static Verb     construct( RandomGenerator* generator, bool plural, Person person );

        Conjugation     conjugation;

        bool            negative; // Has a not
        bool            active; // Switches the subject and object I warned/I was warned.
        bool            subjunctive; // Has a may

        bool            plural;
        Person          person;

        bool            transitive; // Has an object 

        bool            dynamic; // The ing ending TODO IMPLEMENT
    };
}