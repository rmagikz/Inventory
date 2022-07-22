#pragma once

#include "Common.h"
#include "Printing.h"
#include "Item.h"
#include "Category.h"
#include "Exports.h"

void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print);


struct Count {
    std::vector<Item> m_items;
    std::string m_dateOpened;
    std::string m_dateClosed;
    int m_counted;
    int m_total;
    int m_variance;
    bool m_finished;

    Count() : m_counted(0), m_total(0), m_variance(0), m_finished(false) {}

    void Display() {
        std::cout << "Opened:" << m_dateOpened << " | " << "Closed: "
            << m_dateClosed << " | " << "Counted: " << m_counted << " | "
            << "Total: " << m_total << " | " << "Variance: " << m_variance << std::endl;
    }

    bool Exists(const int& uuid) {
        /*    if (m_items.size() < 1) return false;
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
        }*/

        for (int i = 0; i < m_items.size(); i++) {
            if (m_items[i].GetUUID() == uuid) {
                return true;
            }
        }
        return false;
    }
};

class Inventory {
private:
    std::vector<Count> inventoryCounts;
    std::vector<Category> inventoryList;
    int m_count;
    Exports exporter;

    Category* FindCategoryID(const int& categoryId) {
        int left = 0;
        int right = inventoryList.size() - 1;

        while (left <= right) {
            int mid = left + ((right - left) / 2);
            if (std::stoi(inventoryList[mid].m_id) == categoryId) {
                return &inventoryList[mid];
            }
            else if (categoryId < std::stoi(inventoryList[mid].m_id)) {
                right = mid - 1;
            }
            else if (categoryId > std::stoi(inventoryList[mid].m_id)) {
                left = mid + 1;
            }
        }
        return NULL;
    }


    Category* FindCategoryName(const char* categoryName) {
        for (int i = 0; i < inventoryList.size(); i++) {
            if (inventoryList[i].m_name == categoryName) {
                return &inventoryList[i];
            }
        }
        return 0;
    }

    void ResumeCount() {

    }
public:
    Inventory() : m_count(0) {}
    Inventory(const int& count) : m_count(0) { inventoryList.reserve(count); }

    void AddItem(const int& categoryId, const int& count = 1) {
        for (int i = 0; i < count; i++) {
            FindCategoryID(categoryId)->AddItem(m_count);
            m_count++;
        }
    }

    void CreateItem(const char* name, const int& cost) {
        if (FindCategoryName(name)) return;
        Category temp = Category(name, cost);
        temp.AddItem(m_count);
        inventoryList.push_back(temp);
        m_count++;
    }

    void SetStatus(const int& categoryId, const int& itemId, const char* status) {
        if (Category* category = FindCategoryID(categoryId)) category->SetStatus(itemId, status);
    }

    void SetPrice(const int& categoryId, const int& price) {
        if (Category* category = FindCategoryID(categoryId))  category->m_cost = price;
    }

    void GetLabel(const int& categoryId, const int& itemId, const int& print = 0) {
        if (Category* category = FindCategoryID(categoryId)) {
            if (category->FindItemID(itemId)) {
                GenerateLabel(categoryId, itemId, category->m_name, print);
            }
        }
    }

    void Find(const int& categoryId) {
        FindCategoryID(categoryId)->Display();
    }

    void ExportToExcel() {
        exporter.ExportToExcel(inventoryList);
    }

    void ExportToJSON() {
        exporter.ExportToJSON(inventoryList);
    }

    void StartCount() {
        Count count;
        int counted = 0;
        std::string input;

        if (inventoryCounts.size() > 0) {
            if (inventoryCounts.back().m_finished) {
                std::cout << "New Inventory Count | TODAY" << std::endl;
                count.m_dateOpened = "TODAY";
            }
            else {
                std::cout << "Resuming latest count.\nTo open new count please close this one out first by using \"close\"" << std::endl;
                counted = inventoryCounts.back().m_counted;
                count.m_items = std::vector<Item>(inventoryCounts.back().m_items);
                inventoryCounts.pop_back();
            }
        }
        else {
            std::cout << "FIRST INV COUNT" << std::endl;
        }

        while (true) {
            std::cout << "Counted: " << counted << " | Expected: " << m_count << " | Variance : " << counted - m_count << std::endl;
            std::getline(std::cin, input);
            if (input == "exit") { count.m_finished = false; break; }
            if (input == "close") { count.m_dateClosed = "TODAY"; count.m_finished = true; break; }
            try {
                int categoryId = stoi(input.substr(0, input.find("-")));
                int itemId = stoi(input.substr(input.find("-") + 1, input.length()));
                if (Category* category = FindCategoryID(categoryId)) {
                    if (Item* item = category->FindItemID(itemId)) {
                        if (count.Exists(item->GetUUID())) {
                            std::cout << "Already Counted." << std::endl;
                            continue;
                        }
                        category->SetLastCounted(itemId, "Today");
                        count.m_items.push_back((*item));
                        counted++;
                        continue;
                    }
                }
                std::cout << "Item does not belong in inventory." << std::endl;
            }
            catch (...) {
                std::cout << "Invalid input." << std::endl;
            }
        }
        count.m_counted = counted;
        count.m_total = m_count;
        count.m_variance = counted - m_count;
        inventoryCounts.push_back(count);
        std::cout << "Exited." << std::endl;
        std::cout << std::endl;
        DisplayCounts();
    }

    void Display() {
        for (int i = 0; i < inventoryList.size(); i++) {
            inventoryList[i].Display();
        }
    }

    void DisplayCounts() {
        for (int i = 0; i < inventoryCounts.size(); i++) {
            inventoryCounts[i].Display();
        }
    }
};