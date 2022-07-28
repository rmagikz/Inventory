#include "Common.h"
#include "Inventory.h"

int main() {
    CoInitialize(NULL);

    //SETUP
    //DBHandler handler;
    Inventory inventory;

    inventory.CreateItem("iphone x screen/lcd", 179);
    inventory.CreateItem("iphone 11 pro max screen/lcd", 399);
    inventory.CreateItem("iphone 8+ screen/lcd", 99);
    inventory.CreateItem("ipad 10.2 (7th gen) glass", 169);

    for (int i = 10001; i < 10005; i++) {
        inventory.AddItem(i,2);
    }

    inventory.Save();

    inventory.Display();
    //inventory.StartCount();
    //inventory.StartCount();

    //inventory.DisplayCounts(1);
    //inventory.ExportToExcel();
    //inventory.ExportToJSON();
  
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