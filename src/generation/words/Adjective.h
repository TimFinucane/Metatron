#pragma once

#include "grammar/Symbol.h"
#include "Mapping.h"

namespace Generation::Words
{
    std::string adjective( const Grammar::Symbol&, const Mapping& )
    {
        return "blue";
    }
}