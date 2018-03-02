#pragma once

#include "grammar/Symbol.h"
#include "Mapping.h"

namespace Generation::Words
{
    std::string noun( const Grammar::Symbol& word, const Mapping& mapping )
    {
        if( word.checkLink( mapping.link( "has_article" ) ) )
            return "dog";
        else
            return "George";
    }
}