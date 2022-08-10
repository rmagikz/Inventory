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
        void SetId(const std::string& id);
        void SetUUID(const std::string& id);
        void SetDateAdded(const std::string& dateAdded);
        void SetParent(const std::string& parentName);
        void SetLastCounted(const std::string& lastCounted);

        int GetUUID() const;
        std::string GetId() const;
        std::string GetStatus() const;
        std::string GetLastCounted() const;
        std::string GetDateAdded() const;
        std::string GetParentName() const;
    };
}