#pragma once

#include <map>
#include <memory>

#include <Mapping.h>
#include <grammar/String.h>

#include "Word.h"

namespace Generation
{
    class Translator
    {
    public:
        Translator( Mapping& mapping )
            : mapping( mapping )
        {

        }

        template <typename WordType>
        void    addWord( const std::string& symbolName, WordType&& word )
        {
            unsigned int symbolId = mapping.symbols[symbolName];

            words[symbolId] = std::make_unique<WordType>( std::move( word ) );
            words[symbolId]->map( mapping );
        }

        std::string transform( Grammar::String string )
        {
            std::string output = "";

            for( const auto& symbol : string.symbols() )
                output += words[symbol.id]->generate( &symbol ) + " ";

            output.back() = '.';

            return output;
        }

    private:
        Mapping&    mapping;

        std::map<unsigned int, std::unique_ptr<Word>>   words;
    };
}