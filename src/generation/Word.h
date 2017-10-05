#pragma once

#include <grammar/Symbol.h>

namespace Generation
{
    /*
     * Defines a terminal symbol that can generate
     * ouput text.
     */
    class Word
    {
    public:
        virtual ~Word() = default;

        virtual std::string generate( const Grammar::Symbol* symbol ) = 0;
    };
}