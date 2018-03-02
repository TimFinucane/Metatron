#pragma once

#include <map>
#include <memory>
#include <functional>

#include "Mapping.h"
#include "grammar/Symbol.h"

namespace Generation
{
    using Grammar::Symbol;

    /*
     * A translator takes a list of grammar symbols and converts them into
     * a bunch of words
     */
    class Translator
    {
    public:
        using WordGenerator = std::function<std::string( const Symbol&, const Mapping& )>;
    public:
        Translator( const Mapping& mapping )
            : mapping( mapping )
        {
        }

        void    addWord( const std::string& symbolName, const WordGenerator& word )
        {
            words.insert( { mapping.symbols().at( symbolName ), word } );
        }

        std::string transform( const std::list<Symbol>& string )
        {
            std::string output = "";

            for( const auto& symbol : string )
                output += transform( symbol ) + " ";

            output.back() = '.';

            return output;
        }

        std::string transform( const Symbol& symbol )
        {
            return words[symbol.id]( symbol, mapping );
        }

        std::string operator()( const Symbol& symbol )
        {
            return transform( symbol );
        }
        std::string operator()( const std::list<Symbol>& string )
        {
            return transform( string );
        }

    private:
        const Mapping&    mapping;

        std::map<unsigned int, WordGenerator>  words;
    };
}