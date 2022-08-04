#pragma once

#include "Utility.h"

#include <string>

namespace SimpleInventory {

    static enum Status { Available, Sold, Deleted };

    class Item {
    private:
        const char* m_status_names[3] = { "Available", "Sold", "Deleted" };
        std::string m_id;
        int m_uuid;
        std::string m_dateAdded;
        std::string m_parentName;
        std::string m_lastCounted;
        Status m_status;

        Item(const char* parentName, const int& id, const int& uuid);
        Item();

        bool SetStatus(const char* status);
    public:
        Item& operator=(Item& other);

        int GetUUID();
        std::string GetId();
        std::string GetStatus();
        std::string GetLastCounted();
        std::string GetDateAdded();
        std::string GetParentName();
        
        friend class Category;
        friend class DBHandler;
    };
}