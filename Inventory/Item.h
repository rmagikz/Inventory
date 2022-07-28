#pragma once

#include "Common.h"

enum Status { Available, Sold, Deleted };

class Item {
private:
    const char* m_status_names[3] = { "Available", "Sold", "Deleted" };
    const std::string m_id;
    const int m_uuid;
    const char* m_dateAdded;
    const char* m_parentName;
    std::string m_lastCounted;
    Status m_status;

    Item(const char* parentName, const int& id, const int& uuid) 
        : m_id(AssignID(id)), m_uuid(uuid), m_dateAdded(__DATE__), m_parentName(parentName), m_lastCounted("Never"), m_status(Available) {}

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