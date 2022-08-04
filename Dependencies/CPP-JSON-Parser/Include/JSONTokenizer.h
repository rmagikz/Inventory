#pragma once

#include "JSONToken.h"

#include <vector>

namespace JSONparser {
	class Tokenizer {
	private:
		
	public:
		std::vector<Token> Tokenize(const std::string& inputJson);

		std::vector<Token> mTokens;

		void CloseToken(Token& token);
	};
}