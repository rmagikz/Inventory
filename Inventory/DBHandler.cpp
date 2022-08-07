#include "DBHandler.h"

namespace SimpleInventory {

    DBHandler::DBHandler() {}

    void DBHandler::Init(const char* uri, const char* db, const char* collection) {
        m_uri = mongocxx::uri(uri);
        m_client = mongocxx::client(m_uri);
        m_collection = mongocxx::collection(m_client[db][collection]);
    }

    void DBHandler::Save(std::string json) {
        try { Delete(); m_collection.insert_one(bsoncxx::from_json(json)); }
        catch (...) { std::cout << "Could not insert data to DB" << std::endl; }
    }

    std::string DBHandler::Load() {
        try { return bsoncxx::to_json(m_collection.find_one({}).value().view()); }
        catch (...) { std::cout << "Could not find inventory document in DB" << std::endl; }
    }

    void DBHandler::Delete() {
        try { m_collection.delete_one(document{} << "Inventory" << open_document << "$type" << "object" << close_document << finalize); }
        catch (...) { std::cout << "Could not delete DB entry" << std::endl; }
    }
}