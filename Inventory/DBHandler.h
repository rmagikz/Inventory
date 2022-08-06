#pragma once

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

#include <JSONToken.h>
#include <JSONTokenizer.h>
#include <JSONValue.h>
#include <JSONParser.h>

#include <fstream>
#include <iostream>

#include "Category.h"
#include "Item.h"

namespace SimpleInventory {

    using namespace JSONparser;

    class DBHandler {
    private:
        mongocxx::instance m_inst;
        mongocxx::uri m_uri;
        mongocxx::client m_client;
        mongocxx::collection m_collection;
        bsoncxx::oid m_inventoryID;

        std::vector<Category> FromJSON(JSONObject* parsedJSON);

    public:
        DBHandler();

        void Init(const char* uri, const char* db, const char* collection);

        void Save(std::string json);
        std::vector<Category> Load();
        void Delete();
    };
}