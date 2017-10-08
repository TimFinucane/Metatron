#pragma once

#include <map>
#include <string>
#include <istream>
#include <fstream>

#include "Grammar.h"

namespace Grammar
{
    class Reader
    {
    public:
        Reader( Former& former )
            : former( former )
        {
        }

        /*
         * Reads a file, places found productions into the Former, and outputs a map of
         * symbol ids vs their name.
         */
        void    read( const std::string& file );

        unsigned int symbol( const std::string& name )
        {
            return symbolNames[name];
        }

    protected:
        unsigned int    getUniqueId( const std::string& name );

    private:
        Former& former;
        std::map<std::string, unsigned int>     symbolNames;
    };
}