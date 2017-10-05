#pragma once

#include <generation/Word.h>

namespace Generation
{
    namespace Words
    {
        class Article : public Word
        {
        protected:
            std::string produceText()
            {
                return "the";
            }
        };
    }
}