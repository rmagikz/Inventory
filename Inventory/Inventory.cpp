#include "Inventory.h"

namespace SimpleInventory {

    Inventory::Inventory() : db_handler({}), IO({}), localSavePath(""), m_count(0), mSaveMode(LOCAL) {
        CoInitialize(NULL);
    }

    Category* Inventory::FindCategoryID(const int& categoryId) {
        int left = 0;
        int right = inventoryList.size() - 1;

        while (left <= right) {
            int mid = left + ((right - left) / 2);
            if (std::stoi(inventoryList[mid].GetId()) == categoryId) {
                return &inventoryList[mid];
            }
            else if (categoryId < std::stoi(inventoryList[mid].GetId())) {
                right = mid - 1;
            }
            else if (categoryId > std::stoi(inventoryList[mid].GetId())) {
                left = mid + 1;
            }
        }
        return NULL;
    }

    Category* Inventory::FindCategoryName(const char* categoryName) {
        for (int i = 0; i < inventoryList.size(); i++) {
            if (inventoryList[i].GetName() == categoryName) {
                return &inventoryList[i];
            }
        }
        return 0;
    }

    void Inventory::AddItem(const int& categoryId, const int& count) {
        for (int i = 0; i < count; i++) {
            FindCategoryID(categoryId)->AddItem(m_count);
            m_count++;
        }
    }

    void Inventory::CreateItem(const char* name, const int& cost) {
        if (FindCategoryName(name)) return;
        Category temp = Category(name, cost);
        temp.AddItem(m_count);
        inventoryList.push_back(temp);
        m_count++;
    }

    bool Inventory::SetStatus(const int& categoryId, const int& itemId, const char* status) {
        if (Category* category = FindCategoryID(categoryId)) { category->SetStatus(itemId, status); return true; }
        return false;
    }

    bool Inventory::SetPrice(const int& categoryId, const int& price) {
        if (Category* category = FindCategoryID(categoryId)) { category->SetCost(price); return true; }
        return false;
    }

    void Inventory::Find(const int& categoryId) {
        FindCategoryID(categoryId)->Display();
    }

    bool Inventory::GetLabel(const int& categoryId, const int& itemId, const int& print) {
        if (Category* category = FindCategoryID(categoryId)) {
            if (category->FindItemID(itemId)) {
                GenerateLabel(categoryId, itemId, category->GetName(), print);
                return true;
            }
        }
        return false;
    }

    void Inventory::StartCount() {
        currentCount = new Count();
        if (inventoryCounts.size() > 0 && !inventoryCounts.back().m_finished) {
            *currentCount = inventoryCounts.back();
            inventoryCounts.pop_back();
        }
        else {
            currentCount->m_dateOpened = __DATE__;
            currentCount->m_total = m_count;
        }
    }

    int Inventory::CountItem(const std::string& input) {
        try {
            int categoryId = std::stoi(input.substr(0, input.find("-")));
            int itemId = stoi(input.substr(input.find("-") + 1, input.length()));
            if (Category* category = FindCategoryID(categoryId)) {
                if (Item* item = category->FindItemID(itemId)) {
                    if (currentCount->Exists(item->GetUUID())) {
                        return 1;
                    }
                    category->SetLastCounted(itemId, __DATE__);
                    currentCount->m_items.push_back((*item));
                    currentCount->m_counted++;
                }
            }
        }
        catch (...) {
            return 2;
        }
        return 0;
    }

    void Inventory::CloseCount() {
        currentCount->m_dateClosed = __DATE__;
        currentCount->m_finished = true;
        currentCount->m_variance = currentCount->m_counted - m_count;
        inventoryCounts.push_back(*currentCount);
        delete(currentCount);
    }

    void Inventory::ExitCount() {
        currentCount->m_finished = false;
        currentCount->m_variance = currentCount->m_counted - m_count;
        inventoryCounts.push_back(*currentCount);
        delete(currentCount);
    }

    void Inventory::SaveMode(const SAVE_MODE& saveMode) {
        mSaveMode = saveMode;
    }

    void Inventory::InitDB(const char* uri, const char* db, const char* collection) {
        db_handler.Init(uri, db, collection);
    }

    void Inventory::SetSavePath(const char* savePath) {
        localSavePath = savePath;
    }

    void Inventory::ExportToExcel() {
        IO.ExportToExcel(inventoryList);
    }

    void Inventory::Save() {
        if (mSaveMode == LOCAL) {
            if (localSavePath == "") throw std::exception("Save path not set");
            IO.ExportToJSON(inventoryList, inventoryCounts, localSavePath.c_str());
        }
        if (mSaveMode == MONGODB) {
            db_handler.Save(IO.JsonInventory(inventoryList, inventoryCounts));
        }
    }

    void Inventory::Load() {
        if (mSaveMode == LOCAL) {
            if (localSavePath == "") throw std::exception("Save path not set");
            std::string loadedJSON = IO.ImportJSON(localSavePath.c_str());
            inventoryList = IO.FromJSONInventory(loadedJSON);
            inventoryCounts = IO.FromJSONCounts(loadedJSON);
        }
        if (mSaveMode == MONGODB) {
            std::string loadedJSON = db_handler.Load();
            inventoryList = IO.FromJSONInventory(loadedJSON);
            inventoryCounts = IO.FromJSONCounts(loadedJSON);
        }
    }

    void Inventory::Delete() {
        db_handler.Delete();
    }

    void Inventory::Display() {
        for (int i = 0; i < inventoryList.size(); i++) {
            inventoryList[i].Display();
        }
    }

    void Inventory::DisplayCounts(const bool& extra) {
        for (int i = 0; i < inventoryCounts.size(); i++) {
            inventoryCounts[i].Display();
            if (extra) inventoryCounts[i].DisplayItems();
        }
    }

    std::vector<Category> Inventory::GetInventory() const {
        return inventoryList;
    }
    std::vector<Count> Inventory::GetCounts() const {
        return inventoryCounts;
    }
}


