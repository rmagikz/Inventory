#pragma once

#include "Common.h"

using namespace DYMO_Label_Framework;

void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print) {
    std::fstream baseLabel;
    std::fstream newLabel;
    baseLabel.open("baseLabel.label", std::ios::in);
    newLabel.open("newLabel.label", std::ios::out);
    std::string line;
    if (baseLabel.is_open()) {
        while (std::getline(baseLabel, line)) {
            if (line.find("<Text>") != std::string::npos) {
                newLabel << "              <Text>" << categoryId << "-" << itemId << "</Text>\n";
            }
            else if (line.find("<String") != std::string::npos) {
                newLabel << "                   <String xml:space=\"preserve\">" << catName << "</String>\n";
            }
            else { newLabel << line << "\n"; }
        }
        newLabel.close();
        baseLabel.close();
    }

    std::cout << catName << std::endl;
    std::cout << "ID: " << categoryId << "-" << itemId << std::endl;

    if (print) {
        std::cout << "PRINTING LABEL" << std::endl;
        try
        {
            IFrameworkPtr framework(__uuidof(Framework));
            ILabelPtr label = framework->OpenLabel(L"newLabel.label");
            framework->PrintLabel(L"DYMO LabelWriter 450 Turbo", L"", label->SaveToXml(), L"");
        }
        catch (_com_error& e)
        {
            _tprintf_s(_T("Com error was \"%s\", HRESULT 0x%X\n"), e.ErrorMessage(), e.Error());
        }
    }
}



std::string AssignID(int count) {
    return std::to_string(count + 10000);
}

enum Status {
    Available, Sold, Deleted
};

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
        std::cout << categoryName << std::endl;
        for (int i = 0; i < inventoryList.size(); i++) {
            if (inventoryList[i].m_name == categoryName) {
                return &inventoryList[i];
            }
        }
        return 0;
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
        std::cout << name << std::endl;
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

    void Display() {
        for (int i = 0; i < inventoryList.size(); i++) {
            inventoryList[i].Display();
            std::cout << std::endl;
        }
    }
};

// FEATURES

/*  *maintain inventory list
    *add items to inventory
    *change status of items
    *display full inventory
    (current) assign unique identifier to item categories
    (in progress) assign unique identifier to items within categories
    generate labels for items
    search items by label
    generate excel file with full inventory
    allow inventory counts
*/