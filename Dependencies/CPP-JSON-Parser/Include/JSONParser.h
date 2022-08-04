#pragma once

#include "JSONTokenizer.h"
#include "JSONValue.h"

namespace JSONparser {
	class Parser {
	private:
		Tokenizer mTokenizer;
		std::vector<JSONObject*> toDeleteObjects;
		std::vector<JSONList*> toDeleteLists;

		std::vector<Token>::iterator mCurrent;
		std::vector<Token>::iterator mEnd;
	public:

		~Parser();

		JSONObject Parse(std::string inputString);

		bool ExpectKey();
		bool ExpectArray();
		bool ExpectObject();
		bool ExpectOperator(const char* token);
		bool ExpectType(const TOKEN_TYPES& type);
		bool ExpectAssignment(const TOKEN_TYPES& type);
		void ParseInt(JSONObject& currentObject);
		void ParseFloat(JSONObject& currentObject);
		void ParseBool(JSONObject& currentObject);
		void ParseNULL(JSONObject& currentObject);
		void ParseString(JSONObject& currentObject);
		void ParseObject(JSONObject& currentObject);
		void ParseArray(JSONList& currentArray);
	};
}