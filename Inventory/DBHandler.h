#pragma once

#include "Common.h"

class DBHandler {
private:
    mongocxx::instance m_inst;
    mongocxx::uri m_uri;
    mongocxx::client m_client;
    mongocxx::collection m_collection;
    bsoncxx::oid m_inventoryID;

public:
    DBHandler(const char* uri, const char* db, const char* collection)
        : m_uri(uri), m_client(m_uri), m_collection(m_client[db][collection]) {}

    void Save(std::string json) {
        try { m_inventoryID = m_collection.insert_one(bsoncxx::from_json(json).view()).value().inserted_id().get_oid().value; }
        catch (...) { std::cout << "Could not insert data to DB" << std::endl; }
    }

    void Load() {
        try { 
            std::fstream text;
            text.open("dboutput.txt", std::ios::out);
            text << bsoncxx::to_json(m_collection.find_one({}).value().view());
            text.close();
            std::cout << bsoncxx::to_json(m_collection.find_one({}).value().view()) << std::endl;

        }
        catch (...) { std::cout << "Could not find inventory document in DB" << std::endl; }
    }

    void Delete() {
        try { m_client["inventory"].drop(); }
        catch (...) { std::cout << "Could not delete DB entry" << std::endl; }
    }
};