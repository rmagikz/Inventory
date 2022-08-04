#pragma once

#include <string>
#include <iostream>

namespace JSONparser {
	enum TOKEN_TYPES {
		BLANK,
		STRING,
		INT,
		POTENTIAL_FLOAT,
		FLOAT,
		BOOL,
		OPERATOR,
		NULL_VALUE
	};

	class Token {
	public:
		TOKEN_TYPES mType;
		std::string mText;

		Token();

		void display();
	};
}