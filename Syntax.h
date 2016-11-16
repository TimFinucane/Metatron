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

    template <typename T>
    using Synt = std::unique_ptr<T>;

    struct Element
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

    struct Adjective : public Element
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
    struct Demonstrative : public Adjective
    {
        std::string form( RandomGenerator& random, const WordChooser& words );

        bool plural;
    };

    // A complete subject/object
    struct Noun : public Element
    {
        Person  person;
        bool    plural;
    };
    struct Pronoun : public Noun
    {
        std::string form( WordChooser& words );
    };
    struct NounWord : public Noun
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
        std::string form( WordChooser& words );

        Premodifier                     premodifier;
    };

    struct Verb : public Element
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
        std::string form( WordChooser& words );

        Conjugation     conjugation;

        bool            negative; // Has a not
        bool            active; // Switches the subject and object I warned/I was warned.
        bool            subjunctive; // Has a may

        bool            plural;
        Person          person;

        bool            transitive; // Has an object 

        bool            dynamic; // The ing ending TODO IMPLEMENT
    };

    struct Adverb : public Element
    {
        // TODO:
    };

    struct NounPhrase : public Element
    {
        std::string form( WordChooser& words );

        Synt<Noun>                      noun;
        std::vector<Synt<Adjective>>    adjectives;
    };

    // A verb with any number of adverbs attached
    struct VerbPhrase
    {
        std::string form( WordChooser& words );

        Synt<Verb>                  verb;
        std::vector<Synt<Adverb>>   adverbs;
    };
    // A possessive adjective is one which adds an owner (such as father's in father's car)
    struct Possessive : public Adjective
    {
        std::string form( WordChooser& words );

        Synt<NounPhrase> noun;
    };
    
    struct IndependentClause : public Element
    {
        std::string form( WordChooser& words );

        Synt<NounPhrase> subject;
        Synt<VerbPhrase> action;

        // Optional, only if action is transitive
        Synt<NounPhrase> object;
    };
}