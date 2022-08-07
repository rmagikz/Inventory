#include "Count.h"

namespace SimpleInventory {

    Count::Count() : m_counted(0), m_total(0), m_variance(0), m_finished(false) {}

    void Count::Display() {
        std::cout << "Opened: " << m_dateOpened << " | Closed: "
            << m_dateClosed << " | Counted: " << m_counted << " | Total: "
            << m_total << " | Variance: " << m_variance << "\n";
    }

    void Count::DisplayItems() {
        for (int i = 0; i < m_items.size(); i++) {
            std::cout << "  -"
                << m_items[i].GetParentName()
                << " | " << m_items[i].GetId() << " | "
                << m_items[i].GetStatus() << "\n";
        }
        std::cout << "\n";
    }

    bool Count::Exists(const int& uuid) {
        if (m_items.size() < 1) return false;
        int left = 0;
        int right = m_items.size() - 1;

        while (left <= right) {
            int mid = left + ((right - left) / 2);
            if (m_items[mid].GetUUID() == uuid) {
                return true;
            }
            else if (uuid < m_items[mid].GetUUID()) {
                right = mid - 1;
            }
            else if (uuid > m_items[mid].GetUUID()) {
                left = mid + 1;
            }
        }
        return false;
    }
}