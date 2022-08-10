#pragma once

#include "Category.h"
#include "Count.h"

#include <JSONToken.h>
#include <JSONTokenizer.h>
#include <JSONValue.h>
#include <JSONParser.h>

#include <fstream>
#include <sstream>

namespace SimpleInventory {
    using namespace std::string_literals;
    using namespace JSONparser;

    class InvIO {
    public:
        std::string ExportLine(const std::string& content, const std::string& type);
        void LoadCategory(std::string& payload, const Category& category);
        void LoadItem(std::string& payload, const Item& item);
        
        std::string ToJsonString(const std::string& string);
        std::string JsonNumber(const std::string& key, const int& value);
        std::string JsonString(const std::string& key, const std::string& value);
        std::string JsonBool(const std::string& key, const bool& value);
        std::string JsonItem(const std::string& key, const std::vector<Item>& m_items);
    public:
        InvIO();

        std::string ExcelPayload(const std::vector<Category>& inventoryList);
        std::string JsonInventory(const std::vector<Category>& inventoryList, const std::vector<Count>& inventoryCounts);
        std::string JsonCount(const std::vector<Count>& inventoryCounts);

        void ExportToExcel(std::vector<Category>& inventory, const std::string& fileName = "newTable", const std::string& filePath = ".");
        void ExportToJSON(const std::vector<Category>& inventoryList, const std::vector<Count>& counts, const char* path);

        std::string ImportJSON(const char* path);

        std::vector<Category> FromJSONInventory(const std::string& rawJson);
        std::vector<Count> FromJSONCounts(const std::string& rawJson);
    };
}