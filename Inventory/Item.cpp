#include "Item.h"

namespace SimpleInventory {

    Item::Item(const char* parentName, const int& id, const int& uuid)
        : m_id(AssignID(id)), m_uuid(uuid), m_dateAdded(__DATE__), m_parentName(parentName), m_lastCounted("Never"), m_status(Available) {}

    Item::Item() {}

    bool Item::SetStatus(const char* status) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(m_status_names[i], status) == 0) { m_status = (Status)i; return true; }
        }
        return false;
    }

    Item& Item::operator=(Item& other) {
        return *this;
    }

    std::string Item::GetStatus() { return m_status_names[m_status]; }
    std::string Item::GetId() { return m_id; }
    std::string Item::GetLastCounted() { return m_lastCounted; }
    std::string Item::GetParentName() { return m_parentName; }
    std::string Item::GetDateAdded() { return m_dateAdded; }
    int Item::GetUUID() { return m_uuid; }
}