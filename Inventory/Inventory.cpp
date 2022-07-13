#include "Common.h"
#include "Inventory.h"

int main() {
    CoInitialize(NULL);

    //SETUP
    Inventory inventory;

    inventory.CreateItem("iphone x screen/lcd", 179);
    inventory.CreateItem("iphone 11 pro max screen/lcd", 399);
    inventory.CreateItem("iphone 8+ screen/lcd", 99);
    inventory.CreateItem("ipad 10.2 (7th gen) glass", 169);

    for (int i = 10001; i < 10005; i++) {
        inventory.AddItem(i,3);
    }

    //INPUT
    std::cout << "Inventory Program\n\n";
    std::cout << "Please choose one\n\n";
    std::cout << "display       - display full inventory\n";
    std::cout << "createitem    - create new item category\n";
    std::cout << "additem       - add item to existing category\n";
    std::cout << "setprice      - set price for a category\n";
    std::cout << "setstatus     - set status for particular item\n";
    std::cout << "search        - display full inventory\n";
    std::cout << "help          - get help for commands\n";
    std::cout << "exit          - exit program\n\n";

    while (true) {
        std::string input;
        std::getline(std::cin, input);
        std::stringstream stream(input);

        std::vector<std::string> parsedInput;

        while (stream.good()) {
            std::string substr;
            std::getline(stream, substr, ' ');
            parsedInput.push_back(substr);
        }

        if (parsedInput[0] == "exit") { break; }
        if (parsedInput[0] == "display") { inventory.Display(); }

        if (parsedInput[0] == "createitem") {
            if (parsedInput.size() == 3) {
                inventory.CreateItem(parsedInput[1].c_str(), stoi(parsedInput[2]));
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        if (parsedInput[0] == "additem") {
            if (parsedInput.size() == 2) {
                inventory.AddItem(stoi(parsedInput[1]));
            } else if (parsedInput.size() == 3) {
                inventory.AddItem(stoi(parsedInput[1]), stoi(parsedInput[2]));
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        if (parsedInput[0] == "setprice") {
            if (parsedInput.size() == 3) {
                inventory.SetPrice(stoi(parsedInput[1]), stoi(parsedInput[2]));
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        if (parsedInput[0] == "setstatus") {
            if (parsedInput.size() == 4) {
                inventory.SetStatus(stoi(parsedInput[1]), stoi(parsedInput[2]), parsedInput[3].c_str());
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        if (parsedInput[0] == "getlabel") {
            if (parsedInput.size() == 3) {
                inventory.GetLabel(stoi(parsedInput[1]), stoi(parsedInput[2]));
            } else if (parsedInput.size() == 4) {
                inventory.GetLabel(stoi(parsedInput[1]), stoi(parsedInput[2]), stoi(parsedInput[3]));
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        parsedInput = std::vector<std::string>();
    }

}

// FEATURES

/*  *maintain inventory list
    *add items to inventory
    *change status of items
    *display full inventory
    (current) assign unique identifier to item categories
    (in progress) assign unique identifier to items within categories
    generate labels for items
    search items by label
    generate excel file with full inventory
    allow inventory counts
*/