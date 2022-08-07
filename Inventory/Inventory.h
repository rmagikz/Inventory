#pragma once

#include "Printing.h"
#include "Item.h"
#include "Category.h"
#include "InvIO.h"
#include "Count.h"
#include "DBHandler.h"

namespace SimpleInventory {
    void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print);

    static enum SAVE_MODE { LOCAL, MONGODB };

    class Inventory {
    private:
        std::vector<Count> inventoryCounts;
        std::vector<Category> inventoryList;
        DBHandler db_handler;
        InvIO IO;
        int m_count;
        SAVE_MODE mSaveMode;

        Category* FindCategoryID(const int& categoryId);
        Category* FindCategoryName(const char* categoryName);

        void SetupCount(Count& count);
    public:
        Inventory();
        //Inventory(const int& count) : m_count(0) { inventoryList.reserve(count); }

        void AddItem(const int& categoryId, const int& count = 1);
        void CreateItem(const char* name, const int& cost);

        bool SetStatus(const int& categoryId, const int& itemId, const char* status);
        bool SetPrice(const int& categoryId, const int& price);

        bool GetLabel(const int& categoryId, const int& itemId, const int& print = 0);

        void Find(const int& categoryId);

        void ExportToExcel();

        void StartCount();

        void Display();
        void DisplayCounts(const bool& extra);

        void SaveMode(const SAVE_MODE& saveMode);
        void Save();
        void Load();
        void Delete();
    };
}
