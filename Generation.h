#pragma once

#include "Syntax.h"

namespace Syntax
{
    Element<Adjective>  createAdjective( RandomGenerator& random );
    Element<Noun>       createNoun( RandomGenerator& random );
    Element<Verb>       createVerb( RandomGenerator& random );

}