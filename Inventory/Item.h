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
    public:
        Item& operator=(Item& other);

        Item(const char* parentName, const int& id, const int& uuid);
        Item();

        void SetStatus(const char* status);
        void SetId(std::string& id);
        void SetUUID(std::string& id);
        void SetDateAdded(std::string& dateAdded);
        void SetParent(std::string& parentName);
        void SetLastCounted(std::string& lastCounted);

        int GetUUID();
        std::string GetId();
        std::string GetStatus();
        std::string GetLastCounted();
        std::string GetDateAdded();
        std::string GetParentName();
    };
}