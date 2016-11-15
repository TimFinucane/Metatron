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

    struct Element
    {
    public:
        virtual std::string construct();

        virtual ~Element() = 0;
    };

    enum class Person
    {
        FIRST,
        SECOND,
        THIRD
    };
    struct NounPhrase;

    struct Adjective : public Element
    {
        typedef std::unique_ptr<Adjective> Type;
        
        static Type     create( Random* random, const Noun& noun );

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
        Degree degree;
    };
    struct Quantitative : public Adjective
    {
        unsigned int amount;
    };
    struct Demonstrative : public Adjective
    {
        bool plural;
    };

    // A complete subject/object
    struct Noun : public Element
    {
    public:
        typedef std::unique_ptr<Noun> Type;
    public:
        static Type create();

        Person  person;
        bool    plural;
    };
    struct Pronoun : public Noun
    {
        std::string generate();
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
        static NounPhrase               construct( RandomGenerator* generator );

        std::string                     generate();

        std::vector<Adjective::Type>    adjectivePhrases;
        Premodifier                     premodifier;
    };

    struct Qualitative : public Adjective
    {
        Noun::Type noun;
    };

    struct Verb : public Element
    {
    public:
        typedef std::unique_ptr<Verb> Type;

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
        static Verb     construct( RandomGenerator* generator, const Noun& noun );

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
}