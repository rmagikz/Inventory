#include "Item.h"

namespace SimpleInventory {

    Item::Item(const char* parentName, const int& id, const int& uuid)
        : m_id(AssignID(id)), m_uuid(uuid), m_dateAdded(__DATE__), m_parentName(parentName), m_lastCounted("Never"), m_status(Available) {}

    Item::Item() : m_uuid(0), m_status(Available) {}

    Item& Item::operator=(Item& other) {
        return *this;
    }

    void Item::SetId(const std::string& id) { m_id = id; }
    void Item::SetLastCounted(const std::string& lastCounted) { m_lastCounted = lastCounted; }

    void Item::SetUUID(const std::string& id) { m_uuid = std::stoi(id); }
    void Item::SetDateAdded(const std::string& dateAdded) { m_dateAdded = dateAdded; }
    void Item::SetParent(const std::string& parentName) { m_parentName = parentName; }

    void Item::SetStatus(const char* status) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(m_status_names[i], status) == 0) { m_status = (Status)i; }
        }
    }

    std::string Item::GetStatus() const { return m_status_names[m_status]; }
    std::string Item::GetId() const { return m_id; }
    std::string Item::GetLastCounted() const { return m_lastCounted; }
    std::string Item::GetParentName() const { return m_parentName; }
    std::string Item::GetDateAdded() const { return m_dateAdded; }
    int Item::GetUUID() const { return m_uuid; }
}