#pragma once

#include <istream>
#include "RandomGenerator.h"
#include "WordChooser.h"

namespace Syntax
{
    class WordList
    {
    public:
        WordList(){}
        WordList( std::initializer_list<std::string> strings )
        {
            _words = strings;
        }

        void            create( std::istream& file, char endfile );
        
        std::string     chooseRandom( RandomGenerator* random )
        {
            return _words[random->generateInteger( (unsigned int)_words.size() )];
        }
        std::string     operator[]( unsigned int index )
        {
            return _words[index];
        }
        
        size_t          size()
        {
            _words.size();
        }
    private:
        std::vector<std::string> _words;
    };

    class Words : public WordChooser
    {
    public:
        Words( std::istream& adjectives, std::istream& nouns, std::istream& verbs );

        std::string generateNoun( RandomGenerator* random, const NounPhrase& noun );
        std::string generateAdjective( RandomGenerator* random, const AdjectivePhrase& phrase );
        std::string generateVerb( RandomGenerator* random, const Verb& verb );
    private:
        static std::string appendEd( std::string word );
        static std::string appendIng( std::string word );

        WordList nouns;
        WordList basicVerbs;

        WordList adjectives;
        WordList possessives;
    };
}