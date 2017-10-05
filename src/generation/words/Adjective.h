#pragma once

#include <generation/Word.h>

namespace Generation
{
    namespace Words
    {
        class Adjective : public Word
        {
        protected:
            std::string produceText()
            {
                return "blue";
            }
        };
    }
}