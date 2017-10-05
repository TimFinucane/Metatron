#pragma once

#include <map>
#include <memory>

#include <grammar/String.h>

#include "Word.h"

namespace Generation
{
    class Translator
    {
    public:
        template <typename WORD>
        void    addWord( unsigned int symbol, WORD&& word )
        {
            words[symbol] = std::make_unique<WORD>( word );
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
        std::map<unsigned int, std::unique_ptr<Word>> words;
    };
}