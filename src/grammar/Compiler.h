#pragma once

#include <map>
#include <string>
#include <istream>
#include <fstream>

#include <Mapping.h>
#include "Grammar.h"

namespace Grammar
{
    class Compiler
    {
    public:
        /*
         * Reads a file, places found productions into the Former, and outputs a map of
         * symbol ids vs their name.
         */
        void    parseFile( const std::string& file );

        /*
        * Reads a single rule and converts it into a production
        */
        void    parseRule( const std::string& head, const std::string& rule );

        // Members
        const Mapping&  getMapping() const
        {
            return this->mapping;
        }
        const std::multimap<SymbolType,Production>& getProductions() const
        {
            return this->productions;
        }

    private:
        Mapping mapping;
        std::multimap<SymbolType, Production>   productions;
    };

    /*
    * A compilation exception occurs when bad input was passed in.
    */
    class CompilationException : public std::runtime_error
    {
    public:
        explicit CompilationException( Compiler& compiler, const std::string& message )
            : std::runtime_error( "Error trying to read line: " + message ), compiler( compiler )
        {
        }

        Compiler& compiler;
    };
}