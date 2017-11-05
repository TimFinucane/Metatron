#pragma once

#include <generation/WordPart.h>

namespace Generation::Words
{
    std::string noun( const WordPart& word )
    {
        if( word.hasLink( "has_article" ) )
            return "dog";
        else
            return "George";
    }
}