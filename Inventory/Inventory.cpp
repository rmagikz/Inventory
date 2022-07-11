//#include "Common.h"
//#include "Inventory.h"
//
//using namespace DYMO_Label_Framework;
//
//int main() {
//    //SETUP
//    Inventory inventory;
//
//    inventory.CreateItem("iPhone X Screen/LCD", 179);
//    inventory.CreateItem("iPhone 11 Pro Max Screen/LCD", 399);
//    inventory.CreateItem("iPhone 8+ Screen/LCD", 99);
//    inventory.CreateItem("iPad 10.2 (7th Gen) Glass", 169);
//
//    for (int i = 10001; i < 10005; i++) {
//        inventory.AddItem(i,3);
//    }
//
//    //INPUT
//    std::cout << "Inventory Program\n\n";
//    std::cout << "Please choose one\n\n";
//    std::cout << "Display   - display full inventory\n";
//    std::cout << "Add       - add item\n";
//    std::cout << "Search    - display full inventory\n\n";
//
//    while (true) {
//        std::string command, arg1, arg2, arg3;
//        std::cin >> command;
//        if (command == "display") { inventory.Display(); }
//        if (command == "exit") { break; }
//        if (command == "setprice") {
//            std::cin >> arg1 >> arg2;
//            if (arg1.length() != 0 || arg2.length() != 0) {
//                inventory.SetPrice(stoi(arg1), stoi(arg2));
//            }
//        }
//        if (command == "setstatus") {
//            std::cin >> arg1 >> arg2 >> arg3;
//            if (arg1.length() != 0 && arg2.length() != 0) {
//                inventory.SetStatus(stoi(arg1), stoi(arg2), arg3.c_str());
//            }
//        }
//    }
//
//}
//
//// FEATURES
//
///*  *maintain inventory list
//    *add items to inventory
//    *change status of items
//    *display full inventory
//    (current) assign unique identifier to item categories
//    (in progress) assign unique identifier to items within categories
//    generate labels for items
//    search items by label
//    generate excel file with full inventory
//    allow inventory counts
//*/