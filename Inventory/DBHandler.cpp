#include "DBHandler.h"

namespace SimpleInventory {

    DBHandler::DBHandler(const char* uri, const char* db, const char* collection)
        : m_uri(uri), m_client(m_uri), m_collection(m_client[db][collection]) {}

    void DBHandler::Save(std::string json) {
        try { m_collection.insert_one(bsoncxx::from_json(json)); }
        catch (...) { std::cout << "Could not insert data to DB" << std::endl; }
    }

    std::vector<Category> DBHandler::Load() {
        std::string importedJSON;
        try { importedJSON = bsoncxx::to_json(m_collection.find_one({}).value().view()); }
        catch (...) { std::cout << "Could not find inventory document in DB" << std::endl; }

        Parser parser;
        return FromJSON(&parser.Parse(importedJSON));
    }

    std::vector<Category> DBHandler::FromJSON(JSONObject* parsedJSON) {
        std::vector<Category> inventoryList;

        for (int i = 0; i < (*parsedJSON)["Inventory"].mCount; i++) {
            std::string name = (*parsedJSON)["Inventory"][i]["Name"].asString();
            std::string id = (*parsedJSON)["Inventory"][i]["ID"].asString();
            int cost = (*parsedJSON)["Inventory"][i]["Cost"].asInt();

            Category category(name.c_str(), id.c_str(), cost);

            for (int j = 0; j < (*parsedJSON)["Inventory"][i]["Items"].mCount; j++) {
                std::string item_id = (*parsedJSON)["Inventory"][i]["Items"][j]["ID"].asString();
                std::string item_status = (*parsedJSON)["Inventory"][i]["Items"][j]["Status"].asString();
                std::string item_lastCounted = (*parsedJSON)["Inventory"][i]["Items"][j]["Last Counted"].asString();

                Item item;
                item.m_id = item_id;
                item.SetStatus(item_status.c_str());
                item.m_lastCounted = item_lastCounted;

                category.PushItem(item);
            }
            inventoryList.push_back(category);
        }
        return inventoryList;
    }

    void DBHandler::Delete() {
        try { m_client["inventory"].drop(); }
        catch (...) { std::cout << "Could not delete DB entry" << std::endl; }
    }
}