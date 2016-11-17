#pragma once
#include <string>

#include "RandomGenerator.h"

namespace Syntax
{
	// TODO: Some better system which accounts for non-conforming words (good->better->best)
	class WordChooser
	{
	public:
		enum class Word
		{
			NOUN,
			VERB,
			ADJECTIVE,
			ADVERB
		};

		virtual std::string choose( RandomGenerator& random, Word word ) const;
	};
}