#pragma once

#include <generation/Word.h>

namespace Generation
{
    namespace Words
    {
        class Verb : public Word
        {
        protected:
            std::string produceText()
            {
                return "ate";
            }
        };
    }
}