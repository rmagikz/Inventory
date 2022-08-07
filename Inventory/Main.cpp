#include "Inventory.h"
#include <filesystem>

using namespace SimpleInventory;

int main() {
    //SETUP
    //DBHandler handler;
    Inventory inventory;

    inventory.CreateItem("iphone x screen/lcd", 179);
    inventory.CreateItem("iphone 11 pro max screen/lcd", 399);
    inventory.CreateItem("iphone 8+ screen/lcd", 99);
    inventory.CreateItem("ipad 10.2 (7th gen) glass", 169);

    for (int i = 10001; i < 10005; i++) {
        inventory.AddItem(i,4);
    }

    //inventory.SaveMode(MONGODB);
    //inventory.Save();
    //inventory.Load();
    //inventory.Display();
    //inventory.StartCount();
    //inventory.StartCount();
    //inventory.DisplayCounts(1);
    //inventory.ExportToExcel();
  
    //inventory.Delete();

    system("pause");
}

// FEATURES

/*  *maintain inventory list
    *add items to inventory
    *change status of items
    *display full inventory
    *assign unique identifier to item categories
    *assign unique identifier to items within categories
    *generate labels for items
    *search items by label
    *generate excel file with full inventory
    *allow inventory counts
*/

/*

void Inventory::SetupCount(Count& count) {
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


void Inventory::StartCount() {
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

*/