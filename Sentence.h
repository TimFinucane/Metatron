#pragma once

#include <utility>

#include "Syntax.h"
#include "WordGenerator.h"

namespace Syntax
{
    struct IndependentClause
    {
        IndependentClause( RandomGenerator* random )
        {
            subject = NounPhrase::construct( random );
            verb = Verb::construct( random, subject.plural, Person::THIRD );
            if( verb.transitive )
                object = NounPhrase::construct( random );
        }

        std::string construct( RandomGenerator* random, WordGenerator* generator )
        {
            std::string out = generator->generateNoun( random, subject ) + " " +
                generator->generateVerb( random, verb );
            if( verb.transitive )
                out += " " + generator->generateNoun( random, object );
            
            out += ".";

            out[0] = toupper( out[0] );

            return out;
        }

        Noun::Type  subject;
        Verb::Type  verb;

        // Optional
        Noun::Type  object;
    };
}