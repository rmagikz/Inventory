#include "Inventory.h"

using namespace SimpleInventory;

int main() {
    //SETUP
    Inventory inventory;

    inventory.CreateItem("iphone x screen/lcd", 179);
    inventory.CreateItem("iphone 11 pro max screen/lcd", 399);
    inventory.CreateItem("iphone 8+ screen/lcd", 99);
    inventory.CreateItem("ipad 10.2 (7th gen) glass", 169);

    for (int i = 10001; i < 10005; i++) {
        inventory.AddItem(i,4);
    }

    inventory.Display();

    //inventory.SaveMode(MONGODB);
    //inventory.InitDB("URI", "DATABASE", "COLLECTION");
    //inventory.SaveMode(LOCAL);
    //inventory.SetSavePath("C:\\Users\\user\\Desktop\\");
    //inventory.Save();
    //inventory.Load();
    //inventory.StartCount();
    //inventory.DisplayCounts(1);
    //inventory.ExportToExcel();
    //inventory.Delete();

    system("pause");
}