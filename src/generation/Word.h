#pragma once

#include <grammar/Symbol.h>

namespace Generator
{
    /*
     * Defines a terminal symbol that can generate
     * ouput text.
     */
    class Word
    {
    public:
        virtual ~Word() = default;

        virtual std::string generate( Grammar::Symbol* symbol ) = 0;
    };
}