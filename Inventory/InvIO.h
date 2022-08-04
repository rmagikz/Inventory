#pragma once

#include "Category.h"

#include <fstream>

namespace SimpleInventory {
    using namespace std::string_literals;

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

        void ExportToExcel(std::vector<Category>& inventory);
        void ExportToJSON(std::vector<Category>& inventory);
    };
}