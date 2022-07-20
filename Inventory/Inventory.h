#pragma once

#include "Common.h"
#include "Printing.h"
#include "Item.h"
#include "Category.h"
#include "Exports.h"

void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print);

class Inventory {
private:
    std::vector<Category> inventoryList;
    int m_count;
    Exports exporter;

    Category* FindCategoryID(const int& categoryId) {
        int left = 0;
        int right = inventoryList.size();

        while (left < right) {
            int mid = left + ((right - left) / 2);
            if (std::stoi(inventoryList[mid].m_id) == categoryId) {
                return &inventoryList[mid];
            }
            else if (categoryId < std::stoi(inventoryList[mid].m_id)) {
                right = mid;
            }
            else if (categoryId > std::stoi(inventoryList[mid].m_id)) {
                left = mid;
            }
        }
        return NULL;
    }


    Category* FindCategoryName(const char* categoryName) {
        for (int i = 0; i < inventoryList.size(); i++) {
            if (inventoryList[i].m_name == categoryName) {
                return &inventoryList[i];
            }
        }
        return 0;
    }

    std::string ExportString(const std::string& content = "", const std::string& type = "String") {
        return "<ss:Cell><ss:Data ss:Type=\"" + type + "\">" + content + "</ss:Data></ss:Cell>\n";
    }

    void ExportCategory(std::fstream& newTable, Category& category) {
        newTable
            << "<ss:Row>"
            << ExportString(category.m_id, "Number")
            << ExportString() << ExportString(category.m_name)
            << ExportString(std::to_string(category.m_cost), "Number")
            << ExportString()
            << ExportString()
            << "</ss:Row>";
    }

    void ExportItem(std::fstream& newTable, Item& item) {
        newTable
            << "<ss:Row>"
            << ExportString()
            << ExportString(item.m_id, "Number")
            << ExportString()
            << ExportString()
            << ExportString(item.GetStatus())
            << ExportString()
            << "</ss:Row>";
    }

    void WriteToFile(std::fstream& baseTable, std::fstream& newTable) {
        std::string line;
        while (std::getline(baseTable, line)) {
            if (line.find("</ss:Row>") != std::string::npos) {
                newTable << line << std::endl;
                for (int i = 0; i < inventoryList.size(); i++) {
                    ExportCategory(newTable, inventoryList[i]);
                    for (int j = 0; j < inventoryList[i].items.size(); j++) {
                        ExportItem(newTable, inventoryList[i].items[j]);
                    }
                    newTable << "<ss:Row>" << ExportString() << "</ss:Row>";
                }
                newTable << "</ss:Table>";
                newTable << "</ss:Worksheet>";
                newTable << "</ss:Workbook>";
                baseTable.close();
                newTable.close();
                break;
            }
            newTable << line << std::endl;
        }
    }

public:
    Inventory() : m_count(0) {}
    Inventory(const int& count) : m_count(0) { inventoryList.reserve(count); }

    void AddItem(const int& categoryId, const int& count = 1) {
        for (int i = 0; i < count; i++) {
            FindCategoryID(categoryId)->AddItem();
            m_count++;
        }
    }

    void CreateItem(const char* name, const int& cost) {
        if (FindCategoryName(name)) return;
        inventoryList.push_back(Category(name, cost));
        m_count++;
    }

    void SetStatus(const int& categoryId, const int& itemId, const char* status) {
        if (Category* category = FindCategoryID(categoryId)) category->SetStatus(itemId, status);
    }

    void SetPrice(const int& categoryId, const int& price) {
        if (Category* category = FindCategoryID(categoryId))  category->m_cost = price;
    }

    void GetLabel(const int& categoryId, const int& itemId, const int& print = 0) {
        if (Category* category = FindCategoryID(categoryId)) {
            if (category->FindItemID(itemId)) {
                GenerateLabel(categoryId, itemId, category->m_name, print);
            }
        }
    }

    void Find(const int& categoryId) {
        FindCategoryID(categoryId)->Display();
    }

    void ExportToExcel() {
        exporter.ExportToExcel(inventoryList);
    }

    void ExportToJSON() {
        exporter.ExportToJSON(inventoryList);
    }

    void StartCount() {
        int counted = 0;
        std::string input;
        while (true) {
            std::cout << "Counted: " << counted << " | Expected: " << m_count << " | Variance : " << counted - m_count << std::endl;
            std::getline(std::cin, input);
            if (input == "exit") break;
            try {
                int categoryId = stoi(input.substr(0, input.find("-")));
                int itemId = stoi(input.substr(input.find("-") + 1, input.length()));
                if (Category* category = FindCategoryID(categoryId)) {
                    if (category->FindItemID(itemId)) {
                        std::cout << "Counted." << std::endl;
                        counted++;
                    }
                }
                else std::cout << "Item does not belong in inventory." << std::endl;
            }
            catch (...) {
                std::cout << "Invalid input." << std::endl;
            }
        }
        std::cout << "Exited." << std::endl;
    }

    void Display() {
        for (int i = 0; i < inventoryList.size(); i++) {
            inventoryList[i].Display();
        }
    }
};