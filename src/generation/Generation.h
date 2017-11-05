#pragma once

#include <map>
#include <memory>
#include <functional>

#include "Mapping.h"
#include "grammar/Symbol.h"

#include "WordPart.h"

namespace Generation
{
    class Translator
    {
    public:
        using WordGenerator = std::function<std::string( const WordPart& )>;
    public:
        Translator( const Mapping& mapping )
            : mapping( mapping )
        {
        }

        void    addWord( const std::string& symbolName, const WordGenerator& word )
        {
            words.insert( { mapping.symbols.find( symbolName )->second, word } );
        }

        std::string transform( const std::list<Grammar::Symbol>& string )
        {
            std::string output = "";

            for( const auto& symbol : string )
                output += words[symbol.id]( WordPart( mapping, symbol ) ) + " ";

            output.back() = '.';

            return output;
        }

    private:
        const Mapping&    mapping;

        std::map<unsigned int, WordGenerator>  words;
    };
}