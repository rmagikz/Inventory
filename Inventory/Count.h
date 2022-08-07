#pragma once

#include "Item.h"

#include <vector>

namespace SimpleInventory {
    class Count {
    public:
        std::vector<Item> m_items;
        std::string m_dateOpened;
        std::string m_dateClosed;
        int m_counted;
        int m_total;
        int m_variance;
        bool m_finished;

        Count();

        void Display();
        void DisplayItems();
        bool Exists(const int& uuid);
    };
}