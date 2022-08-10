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
    public:
        std::vector<Count> inventoryCounts;
        std::vector<Category> inventoryList;
        Count* currentCount;
        DBHandler db_handler;
        InvIO IO;
        std::string localSavePath;
        int m_count;
        SAVE_MODE mSaveMode;

        Category* FindCategoryID(const int& categoryId);
        Category* FindCategoryName(const char* categoryName);
    public:
        Inventory();

        void AddItem(const int& categoryId, const int& count = 1);
        void CreateItem(const char* name, const int& cost);

        bool SetStatus(const int& categoryId, const int& itemId, const char* status);
        bool SetPrice(const int& categoryId, const int& price);

        void Find(const int& categoryId);

        bool GetLabel(const int& categoryId, const int& itemId, const int& print = 0);

        void StartCount();
        int CountItem(const std::string& input);
        void CloseCount();
        void ExitCount();

        void SaveMode(const SAVE_MODE& saveMode);
        void InitDB(const char* uri, const char* db = "Inventory", const char* collection = "inv0");
        void SetSavePath(const char* savePath);

        void ExportToExcel();
        
        void Save();
        void Load();
        void Delete();

        void Display();
        void DisplayCounts(const bool& extra);

        std::vector<Category> GetInventory() const;
        std::vector<Count> GetCounts() const;
    };
}
