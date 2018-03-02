#pragma once

#include "grammar/Symbol.h"
#include "Mapping.h"

namespace Generation::Words
{
    std::string verb( const Grammar::Symbol&, const Mapping& )
    {
        return "ate";
    }
}