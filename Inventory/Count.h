#pragma once

#include "Common.h"
#include "Item.h"

class Count {
public:
    std::vector<Item> m_items;
    std::string m_dateOpened;
    std::string m_dateClosed;
    int m_counted;
    int m_total;
    int m_variance;
    bool m_finished;

    Count() : m_counted(0), m_total(0), m_variance(0), m_finished(false) {}

    void Display() {
        std::cout << "Opened: " << m_dateOpened << " | Closed: "
            << m_dateClosed << " | Counted: " << m_counted << " | Total: "
            << m_total << " | Variance: " << m_variance << "\n";
    }

    void Status() {
        std::cout << "Counted: " << m_counted << " | Expected: " << m_total << " | Variance : " << m_counted - m_total << "\n";
    }

    void DisplayItems() {
        for (int i = 0; i < m_items.size(); i++) {
            std::cout << "  -"
                << m_items[i].GetParentName()
                << " | " << m_items[i].GetId() << " | "
                << m_items[i].GetStatus() << "\n";
        }
        std::cout << "\n";
    }

    bool Exists(const int& uuid) {
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
};