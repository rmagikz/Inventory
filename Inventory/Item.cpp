#include "Item.h"

namespace SimpleInventory {

    Item::Item(const char* parentName, const int& id, const int& uuid)
        : m_id(AssignID(id)), m_uuid(uuid), m_dateAdded(__DATE__), m_parentName(parentName), m_lastCounted("Never"), m_status(Available) {}

    Item::Item() : m_uuid(0), m_status(Available) {}

    Item& Item::operator=(Item& other) {
        return *this;
    }

    void Item::SetId(std::string& id) { m_id = id; }
    void Item::SetLastCounted(std::string& lastCounted) { m_lastCounted = lastCounted; }

    void Item::SetUUID(std::string& id) { m_uuid = std::stoi(id); }
    void Item::SetDateAdded(std::string& dateAdded) { m_dateAdded = dateAdded; }
    void Item::SetParent(std::string& parentName) { m_parentName = parentName; }

    void Item::SetStatus(const char* status) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(m_status_names[i], status) == 0) { m_status = (Status)i; }
        }
    }

    std::string Item::GetStatus() { return m_status_names[m_status]; }
    std::string Item::GetId() { return m_id; }
    std::string Item::GetLastCounted() { return m_lastCounted; }
    std::string Item::GetParentName() { return m_parentName; }
    std::string Item::GetDateAdded() { return m_dateAdded; }
    int Item::GetUUID() { return m_uuid; }
}