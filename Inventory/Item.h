#pragma once

#include "Common.h"

enum Status { Available, Sold, Deleted };

class Item {
private:
    const char* m_status_names[3] = { "Available", "Sold", "Deleted" };
    const std::string m_id;
    const std::string m_parentName;
    const int m_uuid;
    Status m_status;
    std::string m_lastCounted;

    Item(const std::string& parentName, const int& id, const int& uuid) 
        : m_id(AssignID(id)), m_uuid(uuid), m_status(Available), m_lastCounted("Never"), m_parentName(parentName) {}

    void SetStatus(const char* status) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(m_status_names[i], status) == 0) { m_status = (Status)i; }
        }
    }
public:
    Item& operator=(Item& other) {
        return *this;
    }
    std::string GetStatus() { return m_status_names[m_status]; }
    std::string GetId() { return m_id; }
    std::string GetLastCounted() { return m_lastCounted; }
    std::string GetParentName() { return m_parentName; }
    int GetUUID() { return m_uuid; }

    friend class Category;
};