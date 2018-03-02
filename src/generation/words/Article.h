#pragma once

#include "grammar/Symbol.h"
#include "Mapping.h"

namespace Generation::Words
{
    std::string article( const Grammar::Symbol&, const Mapping& )
    {
        return "the";
    }
}