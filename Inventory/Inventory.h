#pragma once

#include "Common.h"
#include "Printing.h"

void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print);

std::string AssignID(int count) { return std::to_string(count + 10000); }

enum Status { Available, Sold, Deleted };

class Item {
private:
    const char* m_status_names[3] = { "Available", "Sold", "Deleted" };
    Status m_status;
    std::string m_id;

    Item(int id) : m_status(Available), m_id(AssignID(id)) {}

    void SetStatus(const char* status) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(m_status_names[i], status) == 0) { m_status = (Status)i; }
        }
    }

    std::string GetStatus() {
        return m_status_names[m_status];
    }

    friend class Category;
    friend class Inventory;
};

class Category {
private:
    std::vector<Item> items;
    static int count;
    std::string m_id;
    std::string m_name;
    int m_cost;

    Category(const char* name, const int& cost)
        : m_id(AssignID(count)), m_name(name), m_cost(cost) {
        count++;
        items.push_back(Item(items.size()+1));
    }

    Item* FindItemID(const int& itemId) {
        for (int i = 0; i < items.size(); i++) {
            if (std::stoi(items[i].m_id) == itemId) {
                return &items[i];
            }
        }
        return NULL;
    }

    void AddItem() {
        items.push_back(Item(items.size()+1));
    }

    void SetStatus(const int& itemId, const char* status) {
        if (Item* item = FindItemID(itemId)) { item->SetStatus(status); }
    }

    void SetCost(const int& cost) {
        m_cost = cost;
    }

    void Display() {
        std::cout << "ID: " << m_id << " | Name: " << m_name << " | Cost: " << m_cost << std::endl;
        for (int i = 0; i < items.size(); i++) {
            std::cout << "  - ID: " << items[i].m_id << " | " << items[i].m_status_names[items[i].m_status] << std::endl;
        }
        std::cout << std::endl;
    }

    friend class Inventory;
};

int Category::count = 1;

class Inventory {
private:
    std::vector<Category> inventoryList;

    Category* FindCategoryID(const int& categoryId) {
        for (int i = 0; i < inventoryList.size(); i++) {
            if (std::stoi(inventoryList[i].m_id) == categoryId) {
                return &inventoryList[i];
            }
        }
        return 0;
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
        return "<ss:Cell><ss:Data ss:Type=\"" + type + "\">" + content + "</ss:Data></ss:Cell>";
    }

    bool ExportToExcelBase() {
        std::fstream baseTable;
        std::fstream newTable;
        baseTable.open("baseTable.xml", std::ios::in);
        newTable.open("newTable.xml", std::ios::out);
        std::string line;
        if (baseTable.is_open()) {
            while (std::getline(baseTable, line)) {
                if (line.find("</ss:Row>") != std::string::npos) {
                    newTable << line << std::endl;
                    for (int i = 0; i < inventoryList.size(); i++) {
                        newTable
                            << "<ss:Row>" << std::endl
                            << ExportString(inventoryList[i].m_id, "Number") << std::endl
                            << ExportString() << ExportString(inventoryList[i].m_name) << std::endl
                            << ExportString(std::to_string(inventoryList[i].m_cost), "Number") << std::endl
                            << ExportString() << std::endl
                            << ExportString() << std::endl
                            << "</ss:Row>" << std::endl;
                        for (int j = 0; j < inventoryList[i].items.size(); j++) {
                            newTable
                                << "<ss:Row>" << std::endl
                                << ExportString() << std::endl
                                << ExportString(inventoryList[i].items[j].m_id, "Number") << std::endl
                                << ExportString() << std::endl
                                << ExportString() << std::endl
                                << ExportString(inventoryList[i].items[j].GetStatus()) << std::endl
                                << ExportString() << std::endl
                                << "</ss:Row>" << std::endl;
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
        return true;
    }
public:
    Inventory() {}
    Inventory(const int& count) { inventoryList.reserve(count); }

    void AddItem(const int& categoryId, const int& count = 1) {
        for (int i = 0; i < count; i++) {
            FindCategoryID(categoryId)->AddItem();
        }
    }

    void CreateItem(const char* name, const int& cost) {
        if (FindCategoryName(name)) return;
        inventoryList.push_back(Category(name, cost));
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

    bool ExportToExcel() {
        return ExportToExcelBase();
    }

    void Display() {
        for (int i = 0; i < inventoryList.size(); i++) {
            inventoryList[i].Display();
        }
    }
};

// FEATURES

/*  *maintain inventory list
    *add items to inventory
    *change status of items
    *display full inventory
    *assign unique identifier to item categories
    *assign unique identifier to items within categories
    *generate labels for items
    *search items by label
    *generate excel file with full inventory
    allow inventory counts
*/