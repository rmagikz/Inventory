#pragma once

#include "Common.h"
#include "Item.h"

class Category {
private:
    std::vector<Item> items;
    static int count;
    std::string m_id;
    std::string m_name;
    int m_cost;

    Category(const char* name, const int& cost)
        : m_id(AssignID(count)), m_name(name), m_cost(cost) {
        Category::AddItem();
        count++;
    }

    Item* FindItemID(const int& itemId) {
        int left = 0;
        int right = items.size();

        while (left < right) {
            int mid = left + ((right - left) / 2);
            if (std::stoi(items[mid].m_id) == itemId) {
                return &items[mid];
            }
            else if (itemId < std::stoi(items[mid].m_id)) {
                right = mid;
            }
            else if (itemId > std::stoi(items[mid].m_id)) {
                left = mid;
            }
        }
        return NULL;
    }

    void AddItem() {
        items.push_back(Item(items.size() + 1));
    }

    void SetStatus(const int& itemId, const char* status) {
        if (Item* item = FindItemID(itemId)) item->SetStatus(status);
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
    friend class Exports;
};

int Category::count = 1;
