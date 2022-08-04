#pragma once

#include "Item.h"
#include "Utility.h"

#include <vector>

namespace SimpleInventory {
    class Category {
    private:
        std::vector<Item> m_items;
        static int count;
        const std::string m_id;
        const char* m_name;
        int m_cost;

        Category(const char* name, const int& cost);
        Category(const char* name, const char* id, const int& cost);

        Item* FindItemID(const int& itemId);
        void AddItem(const int& uuid);
        void PushItem(Item& item);
        void SetCost(const int& cost);
        bool SetStatus(const int& itemId, const char* status);
        bool SetLastCounted(const int& itemId, const char* lastCounted);

        void Display();
    public:
        std::vector<Item>* GetItems();
        std::string GetId();
        std::string GetName();
        int GetCost();

        friend class Inventory;
        friend class DBHandler;
    };
}