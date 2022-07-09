#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std::string_literals;

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
            if (status == m_status_names[i]) { m_status = (Status)i; }
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
    const char* m_name;
    int m_cost;

    Category(const char* name, const int& cost)
        : m_id(AssignID(count)), m_name(name), m_cost(cost) {
        count++;
        items.push_back(Item(items.size()+1));
    }

    Item* FindItemID(int itemId) {
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

    void SetCost(int& cost) {
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

    Category* FindCategoryID(int categoryId) {
        for (int i = 0; i < inventoryList.size(); i++) {
            if (std::stoi(inventoryList[i].m_id) == categoryId) {
                return &inventoryList[i];
            }
        }
        return 0;
    }
public:
    Inventory() {}
    Inventory(const int& count) { inventoryList.reserve(count); }

    //ADD ONE ITEM TO CATEGORY
    void AddItem(int categoryId) {
        FindCategoryID(categoryId)->AddItem();
    }

    //ADD MULTIPLE ITEMS TO CATEGORY
    void AddItem(int categoryId, int count) {
        for (int i = 0; i < count; i++) {
            AddItem(categoryId);
        }
    }

    //ADD NEW ITEM AND CREATES CATEGORY FOR IT | DOES NOT WORK IF CATEGORY WITH SAME NAME ALREADY EXISTS
    void CreateItem(const char* name, const int& cost) {
        for (int i = 0; i < inventoryList.size(); i++) {
            if (inventoryList[i].m_name == name) {
                return;
            }
        }
        inventoryList.push_back(Category(name, cost));
    }

    void SetStatus(int categoryId, int itemId, const char* status) {
        if (Category* category = FindCategoryID(categoryId)) {
            if (Item* item = category->FindItemID(itemId)) {
                item->SetStatus(status);
            }
        }
    }

    int SetPrice(const char* name, int price) {
        for (int i = 0; i < inventoryList.size(); i++) {
            if (inventoryList[i].m_name == name) {
                inventoryList[i].m_cost = price;
                return 1;
            }
        }
        return 0;
    }

    //int SetPrice(int categoryId, int price) {
    //    for (int i = 0; i < inventoryList.size(); i++) {
    //        if (inventoryList[i].m_id == categoryId) {
    //            inventoryList[i].m_cost = price;
    //            return 1;
    //        }
    //    }
    //    return 0;
    //}

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