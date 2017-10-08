#pragma once

#include <generation/Word.h>

namespace Generation
{
    namespace Words
    {
        class Noun : public Word
        {
        protected:
            std::string produceText()
            {
                if( hasLink( "has_article" ) )
                    return "dog";
                else
                    return "George";
            }
        };
    }
}