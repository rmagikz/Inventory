#pragma once

#include "Common.h"
#include "Printing.h"
#include "Item.h"
#include "Category.h"
#include "Exports.h"
#include "Count.h"

void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print);

class DBHandler {
private:
    mongocxx::instance m_inst;
    mongocxx::uri m_uri;
    mongocxx::client m_client;
    mongocxx::collection m_collection;
    bsoncxx::oid m_inventoryID;
    
public:
    DBHandler(const char* uri, const char* db, const char* collection) 
        : m_uri(uri), m_client(m_uri), m_collection(m_client[db][collection]) {

    }

    void Save(std::string json) {
        m_inventoryID = m_collection.insert_one(bsoncxx::from_json(json).view()).value().inserted_id().get_oid().value;
    }

    void Load() {
        try { std::cout << bsoncxx::to_json(m_collection.find_one(document{} << "_id" << m_inventoryID << finalize).value().view()) << std::endl; }
        catch (...) { std::cout << "COULDNT FIND" << std::endl; }
    }

    void Delete() {
        m_client["inventory"].drop();
    }
};

class Inventory {
private:
    std::vector<Count> inventoryCounts;
    std::vector<Category> inventoryList;
    Exports exporter;
    DBHandler db_handler;
    int m_count;

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

    void SetupCount(Count& count) {
        if (inventoryCounts.size() > 0 && !inventoryCounts.back().m_finished) {
            std::cout << "Resuming latest count.\nTo open new count please close this one out first by using \"close\"\n";
            count = inventoryCounts.back();
            inventoryCounts.pop_back();
        }
        else {
            count.m_dateOpened = __DATE__;
            count.m_total = m_count;
            count.Display();
        }
    }
public:
    Inventory() : m_count(0), db_handler("mongodb+srv://magikz:Jessyca121@inv0.kwfwq.mongodb.net/?retryWrites=true&w=majority","inventory","inv0") {}
    //Inventory(const int& count) : m_count(0) { inventoryList.reserve(count); }

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
        SetupCount(count);
        std::string input;
        while (true) {
            std::getline(std::cin, input);
            if (input == "exit") { count.m_finished = false; break; }
            if (input == "close") { count.m_dateClosed = __DATE__; count.m_finished = true; break; }
            if (input == "status") { count.Status(); continue; }
            try {
                int categoryId = stoi(input.substr(0, input.find("-")));
                int itemId = stoi(input.substr(input.find("-") + 1, input.length()));
                if (Category* category = FindCategoryID(categoryId)) {
                    if (Item* item = category->FindItemID(itemId)) {
                        if (count.Exists(item->GetUUID())) {
                            std::cout << "Already Counted.\n";
                            continue;
                        }
                        category->SetLastCounted(itemId, __DATE__);
                        count.m_items.push_back((*item));
                        count.m_counted++;
                        continue;
                    }
                }
                std::cout << "Item does not belong in inventory.\n";
            }
            catch (...) {
                std::cout << "Invalid input.\n";
            }
        }
        count.m_variance = count.m_counted - m_count;
        inventoryCounts.push_back(count);
        std::cout << "Exited.\n";
        std::cout << "\n";
    }

    void Display() {
        for (int i = 0; i < inventoryList.size(); i++) {
            inventoryList[i].Display();
        }
    }

    void DisplayCounts(const bool& extra) {
        for (int i = 0; i < inventoryCounts.size(); i++) {
            inventoryCounts[i].Display();
            if (extra) inventoryCounts[i].DisplayItems();
        }
    }

    void Save() {
        db_handler.Save(exporter.JsonPayload(inventoryList));
    }

    void Load() {
        db_handler.Load();
    }

    void Delete() {
        db_handler.Delete();
    }
};


