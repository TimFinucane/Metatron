#pragma once

#include <string>

#include "Formation.h"

namespace Syntax
{
    class WordGenerator abstract
    {
    public:
        virtual std::string generateNoun( RandomGenerator* random, const NounPhrase& noun ) = 0;
        virtual std::string generateAdjective( RandomGenerator* random, const AdjectivePhrase& phrase ) = 0;
        virtual std::string generateVerb( RandomGenerator* random, const Verb& verb ) = 0;
    };
}