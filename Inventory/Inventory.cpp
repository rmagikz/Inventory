#include "Common.h"
#include "Inventory.h"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

double Benchmark1() {
    std::vector<double> runs;

    for (int i = 0; i < 100000; i++) {
        auto t1 = high_resolution_clock::now();
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        runs.push_back(ms_double.count());
    }
    double total = 0;
    for (int i = 0; i < runs.size(); i++) {
        total += runs[i];
    }

    return total / runs.size();
}

int main() {
    CoInitialize(NULL);

    //SETUP
    Inventory inventory;

    inventory.CreateItem("iphone x screen/lcd", 179);
    inventory.CreateItem("iphone 11 pro max screen/lcd", 399);
    inventory.CreateItem("iphone 8+ screen/lcd", 99);
    inventory.CreateItem("ipad 10.2 (7th gen) glass", 169);
    inventory.CreateItem("1", 169);
    inventory.CreateItem("2", 169);
    inventory.CreateItem("3", 169);
    inventory.CreateItem("4", 169);
    inventory.CreateItem("5", 169);
    inventory.CreateItem("6", 169);
    inventory.CreateItem("7", 169);
    inventory.CreateItem("8", 169);
    inventory.CreateItem("9", 169);
    inventory.CreateItem("10", 169);
    inventory.CreateItem("11", 169);
    inventory.CreateItem("12", 169);
    inventory.CreateItem("13", 169);
    inventory.CreateItem("14", 169);
    inventory.CreateItem("15", 169);
    inventory.CreateItem("16", 169);
    inventory.CreateItem("17", 169);
    inventory.CreateItem("18", 169);
    inventory.CreateItem("19", 169);
    inventory.CreateItem("20", 169);

    for (int i = 10001; i < 10025; i++) {
        inventory.AddItem(i,60);
    }

    inventory.Display();
    inventory.ExportToExcel();

  
    system("pause");
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

/*
//INPUT
    std::cout << "Inventory Program\n\n";
    std::cout << "Please choose one\n\n";
    std::cout << "display       - display full inventory\n";
    std::cout << "createitem    - create new item category\n";
    std::cout << "additem       - add item to existing category\n";
    std::cout << "setprice      - set price for a category\n";
    std::cout << "setstatus     - set status for particular item\n";
    std::cout << "find        - find category\n";
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
        if (parsedInput[0] == "display") { std::cout << std::endl; inventory.Display(); }

        //if (parsedInput[0] == "createitem") {
        //    if (parsedInput.size() == 3) {
        //        inventory.CreateItem(parsedInput[1].c_str(), stoi(parsedInput[2]));
        //    } else { std::cout << "Invalid Syntax." << std::endl; }
        //}

        if (parsedInput[0] == "additem") {
            std::cout << std::endl;
            if (parsedInput.size() == 2) {
                inventory.AddItem(stoi(parsedInput[1]));
            } else if (parsedInput.size() == 3) {
                inventory.AddItem(stoi(parsedInput[1]), stoi(parsedInput[2]));
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        if (parsedInput[0] == "setprice") {
            std::cout << std::endl;
            if (parsedInput.size() == 3) {
                inventory.SetPrice(stoi(parsedInput[1]), stoi(parsedInput[2]));
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        if (parsedInput[0] == "setstatus") {
            std::cout << std::endl;
            if (parsedInput.size() == 4) {
                inventory.SetStatus(stoi(parsedInput[1]), stoi(parsedInput[2]), parsedInput[3].c_str());
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        if (parsedInput[0] == "find") {
            std::cout << std::endl;
            if (parsedInput.size() == 2) {
                inventory.Find(stoi(parsedInput[1]));
            }
        }

        if (parsedInput[0] == "getlabel") {
            std::cout << std::endl;
            if (parsedInput.size() == 3) {
                inventory.GetLabel(stoi(parsedInput[1]), stoi(parsedInput[2]), 0);
            } else if (parsedInput.size() == 4) {
                inventory.GetLabel(stoi(parsedInput[1]), stoi(parsedInput[2]), stoi(parsedInput[3]));
            } else { std::cout << "Invalid Syntax." << std::endl; }
        }

        parsedInput = std::vector<std::string>();
    }*/