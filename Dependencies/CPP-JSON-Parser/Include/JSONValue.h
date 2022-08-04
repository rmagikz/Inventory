#pragma once

#include <unordered_map>
#include <iostream>

namespace JSONparser {

	struct JSONValue {

		using JSONList = std::vector<JSONValue>;
		using JSONObject = std::unordered_map<std::string, JSONValue>;

		static enum DATA_TYPES {
			OBJECT, LIST, STRING, FLOAT, INT, BOOL, NULL_VALUE
		} data_types;

		union DATA {
			JSONObject* JSONObject;
			JSONList* JSONList;
			std::string* JSONString;
			short JSONNULL;
			float JSONFloat;
			int JSONInt;
			bool JSONBool;
		} mData;

		DATA_TYPES mDataType;
		size_t mCount;

		void SetObject(JSONObject* data);
		void SetList(JSONList* data);
		void SetString(std::string* data);
		void SetNULL();
		void SetFloat(const float& data);
		void SetInt(const int& data);
		void SetBool(const bool& data);

		std::string asString();
		float asFloat();
		int asInt();
		bool asBool();
		short asNULL();

		JSONValue operator[](std::string key);
		JSONValue operator[](int index);

		void Display();
	};

	using JSONList = std::vector<JSONValue>;
	using JSONObject = std::unordered_map<std::string, JSONValue>;
}