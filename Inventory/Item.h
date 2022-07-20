#pragma once

#include "Common.h"

enum Status { Available, Sold, Deleted };

class Item {
private:
    const char* m_status_names[3] = { "Available", "Sold", "Deleted" };
    Status m_status;
    std::string m_id;

    Item(int id) : m_status(Available), m_id(AssignID(id)) {}

    void SetStatus(const char* status) {
        for (int i = 0; i < 3; i++) {
            if (strcmp(m_status_names[i], status) == 0) { m_status = (Status)i; }
        }
    }

    std::string GetStatus() {
        return m_status_names[m_status];
    }

    friend class Category;
    friend class Inventory;
    friend class Exports;
};