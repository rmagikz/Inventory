#pragma once

#include "Category.h"

#include <JSONToken.h>
#include <JSONTokenizer.h>
#include <JSONValue.h>
#include <JSONParser.h>

#include <fstream>

namespace SimpleInventory {
    using namespace std::string_literals;
    using namespace JSONparser;

    class InvIO {
    public:
        std::string ExportLine(const std::string& content, const std::string& type);
        void LoadCategory(std::string& payload, Category& category);
        void LoadItem(std::string& payload, Item& item);
        
        std::string ToJsonString(const std::string& string);
        std::string JsonNumber(const std::string& key, const int& value);
        std::string JsonString(const std::string& key, const std::string& value);
        std::string JsonItem(const std::string& key, std::vector<Item>& m_items);
    public:
        InvIO();

        std::string ExcelPayload(std::vector<Category>& inventoryList);
        std::string JsonPayload(std::vector<Category>& inventoryList);

        void ExportToExcel(std::vector<Category>& inventory, const std::string& fileName = "newTable", const std::string& filePath = ".");
        void ExportToJSON(std::vector<Category>& inventory);

        std::vector<Category> FromJSON(const std::string& rawJson);
    };
}