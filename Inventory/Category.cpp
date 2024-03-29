#include "Category.h"

namespace SimpleInventory {

    Category::Category(const char* name, const int& cost)
        : m_id(AssignID(count)), m_name(name), m_cost(cost) {
        count++;
    }

    Category::Category(const char* name, const char* id, const int& cost)
        : m_id(id), m_name(name), m_cost(cost) {
        count++;
    }

    Item* Category::FindItemID(const int& itemId) {
        int left = 0;
        int right = m_items.size() - 1;

        while (left <= right) {
            int mid = left + ((right - left) / 2);
            if (std::stoi(m_items[mid].GetId()) == itemId) {
                return &m_items[mid];
            }
            else if (itemId < std::stoi(m_items[mid].GetId())) {
                right = mid - 1;
            }
            else if (itemId > std::stoi(m_items[mid].GetId())) {
                left = mid + 1;
            }
        }
        return NULL;
    }

    void Category::AddItem(const int& uuid) {
        m_items.push_back(Item(m_name, m_items.size() + 1, uuid));
    }

    void Category::PushItem(const Item& item) {
        m_items.push_back(item);
    }

    void Category::Display() {
        std::cout << "ID: " << m_id << " | Name: " << m_name << " | Cost: " << m_cost << "\n";
        for (int i = 0; i < m_items.size(); i++) {
            std::cout << "  - ID: " << m_items[i].GetId() << " | Added: " << m_items[i].GetDateAdded() << " | " << m_items[i].GetStatus() << "\n";
        }
        std::cout << "\n";
    }

    void Category::SetCost(const int& cost) {
        m_cost = cost;
    }

    bool Category::SetStatus(const int& itemId, const char* status) {
        if (Item* item = FindItemID(itemId)) { item->SetStatus(status); return true; }
        return false;
    }

    bool Category::SetLastCounted(const int& itemId, const char* lastCounted) {
        if (Item* item = FindItemID(itemId)) { item->GetLastCounted() = lastCounted; return true; }
        return false;
    }

    std::vector<Item> Category::GetItems() const { return m_items; }
    std::string Category::GetId() const { return m_id; }
    std::string Category::GetName() const { return m_name; }
    int Category::GetCost() const { return m_cost; }

    int Category::count = 1;
}