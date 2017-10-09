#pragma once

#include <map>
#include <memory>

#include "Mapping.h"
#include "grammar/Symbol.h"

#include "Word.h"

namespace Generation
{
    class Translator
    {
    public:
        Translator( const Mapping& mapping )
            : mapping( mapping )
        {
        }

        template <typename WordType>
        void    addWord( const std::string& symbolName, WordType&& word )
        {
            unsigned int symbolId = mapping.symbols.find( symbolName )->second;

            words[symbolId] = std::make_unique<WordType>( std::move( word ) );
            words[symbolId]->map( mapping );
        }

        std::string transform( const std::list<Grammar::Symbol>& string )
        {
            std::string output = "";

            for( const auto& symbol : string )
                output += words[symbol.id]->generate( &symbol ) + " ";

            output.back() = '.';

            return output;
        }

    private:
        const Mapping&    mapping;

        std::map<unsigned int, std::unique_ptr<Word>>   words;
    };
}