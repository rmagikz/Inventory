#pragma once

#include "Common.h"
#include "Item.h"

class Category {
private:
    std::vector<Item> m_items;
    static int count;
    std::string m_id;
    std::string m_name;
    int m_cost;

    Category(const char* name, const int& cost)
        : m_id(AssignID(count)), m_name(name), m_cost(cost) {
        count++;
    }

    Item* FindItemID(const int& itemId) {
        int left = 0;
        int right = m_items.size() - 1;

        while (left <= right) {
            int mid = left + ((right - left) / 2);
            if (std::stoi(m_items[mid].m_id) == itemId) {
                return &m_items[mid];
            }
            else if (itemId < std::stoi(m_items[mid].m_id)) {
                right = mid - 1;
            }
            else if (itemId > std::stoi(m_items[mid].m_id)) {
                left = mid + 1;
            }
        }
        return NULL;
    }
    
    void AddItem(const int& uuid) {
        m_items.push_back(Item(m_name,m_items.size() + 1, uuid));
    }

    void SetStatus(const int& itemId, const char* status) {
        if (Item* item = FindItemID(itemId)) item->SetStatus(status);
    }

    void SetLastCounted(const int& itemId, const char* lastCounted) {
        if (Item* item = FindItemID(itemId)) item->m_lastCounted = lastCounted;
    }

    void SetCost(const int& cost) {
        m_cost = cost;
    }

    void Display() {
        std::cout << "ID: " << m_id << " | Name: " << m_name << " | Cost: " << m_cost << "\n";
        for (int i = 0; i < m_items.size(); i++) {
            std::cout << "  - ID: " << m_items[i].m_id << " | " << m_items[i].GetStatus() << " | Last Counted: " << m_items[i].m_lastCounted << " | UUID: " << m_items[i].m_uuid << "\n";
        }
        std::cout << "\n";
    }
public:
    std::vector<Item>* GetItems() {
        return &m_items;
    }

    std::string GetId() {
        return m_id;
    }

    std::string GetName() {
        return m_name;
    }

    int GetCost() {
        return m_cost;
    }

    friend class Inventory;
};

int Category::count = 1;
