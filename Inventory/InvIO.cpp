#include "InvIO.h"

namespace SimpleInventory {

    std::string InvIO::ExportLine(const std::string& content = "", const std::string& type = "String") {
        return "<ss:Cell><ss:Data ss:Type=\"" + type + "\">" + content + "</ss:Data></ss:Cell>\n";
    }

    void InvIO::LoadCategory(std::string& payload, const Category& category) {
        payload
            += "<ss:Row>"
            + ExportLine(category.GetId(), "Number")
            + ExportLine()
            + ExportLine(category.GetName())
            + ExportLine(std::to_string(category.GetCost()), "Number")
            + ExportLine()
            + ExportLine()
            + "</ss:Row>";
    }

    void InvIO::LoadItem(std::string& payload, const Item& item) {
        payload
            += "<ss:Row>"
            + ExportLine()
            + ExportLine(item.GetId(), "Number")
            + ExportLine()
            + ExportLine()
            + ExportLine(item.GetStatus())
            + ExportLine()
            + "</ss:Row>";
    }

    std::string InvIO::ExcelPayload(const std::vector<Category>& inventoryList) {
        std::string payload;
        for (int i = 0; i < inventoryList.size(); i++) {
            LoadCategory(payload, inventoryList[i]);
            for (int j = 0; j < inventoryList[i].GetItems().size(); j++) {
                LoadItem(payload, inventoryList[i].GetItems()[j]);
            }
            payload += "<ss:Row>" + ExportLine() + "</ss:Row>";
        }
        payload += "</ss:Table>";
        payload += "</ss:Worksheet>";
        payload += "</ss:Workbook>";
        return payload;
    }

    std::string InvIO::ToJsonString(const std::string& string) {
        return "\"" + string + "\"";
    }

    std::string InvIO::JsonNumber(const std::string& key, const int& value) {
        return ToJsonString(key) + " : " + std::to_string(value);
    }

    std::string InvIO::JsonString(const std::string& key, const std::string& value) {
        return ToJsonString(key) + " : " + ToJsonString(value);
    }

    std::string InvIO::JsonBool(const std::string& key, const bool& value) {
        return ToJsonString(key) + " : " + (value == 0 ? "false": "true");
    }

    std::string InvIO::JsonItem(const std::string& key, const std::vector<Item>& m_items) {
        std::string result;
        result += ToJsonString(key) + " : [\n";
        for (int i = 0; i < m_items.size(); i++) {
            result += "\t\t\t\t{\n";
            result += "\t\t\t\t\t" + JsonString("ID", m_items[i].GetId()) + ",\n";
            result += "\t\t\t\t\t" + JsonString("UUID", std::to_string(m_items[i].GetUUID())) + ",\n";
            result += "\t\t\t\t\t" + JsonString("Parent Category", m_items[i].GetParentName()) + ",\n";
            result += "\t\t\t\t\t" + JsonString("Status", m_items[i].GetStatus()) + ",\n";
            result += "\t\t\t\t\t" + JsonString("Last Counted", m_items[i].GetLastCounted()) + ",\n";
            result += "\t\t\t\t\t" + JsonString("Date Added", m_items[i].GetDateAdded()) + "\n";
            if (i == m_items.size() - 1) { result += "\t\t\t\t}\n"; }
            else { result += "\t\t\t\t},\n"; }
        }
        result += "\t\t\t]\n";
        return result;
    }

    std::string InvIO::JsonInventory(const std::vector<Category>& inventoryList, const std::vector<Count>& inventoryCounts) {
        std::string payload;
        payload += "{\n";
        payload += "\t" + ToJsonString("Inventory") + " : [\n";
        for (int i = 0; i < inventoryList.size(); i++) {
            payload += "\t\t{\n";
            payload += "\t\t\t" + JsonString("Name", inventoryList[i].GetName()) + ",\n";
            payload += "\t\t\t" + JsonString("ID", inventoryList[i].GetId()) + ",\n";
            payload += "\t\t\t" + JsonNumber("Cost", inventoryList[i].GetCost()) + ",\n";
            payload += "\t\t\t" + JsonItem("Items", inventoryList[i].GetItems());
            if (i == inventoryList.size() - 1) { payload += "\t\t}\n"; }
            else { payload += "\t\t},\n"; }
        }
        payload += "\t],\n";
        payload += JsonCount(inventoryCounts);
        return payload;
    }

    std::string InvIO::JsonCount(const std::vector<Count>& inventoryCounts) {
        std::string payload;
        payload += "\t" + ToJsonString("Counts") + " : [\n";
        for (int i = 0; i < inventoryCounts.size(); i++) {
            payload += "\t\t{\n";
            payload += "\t\t\t" + JsonString("Date Opened", inventoryCounts[i].m_dateOpened) + ",\n";
            payload += "\t\t\t" + JsonString("Date Closed", inventoryCounts[i].m_dateClosed) + ",\n";
            payload += "\t\t\t" + JsonNumber("Total", inventoryCounts[i].m_total) + ",\n";
            payload += "\t\t\t" + JsonNumber("Counted", inventoryCounts[i].m_counted) + ",\n";
            payload += "\t\t\t" + JsonNumber("Variance", inventoryCounts[i].m_variance) + ",\n";
            payload += "\t\t\t" + JsonBool("Finished", inventoryCounts[i].m_finished) + ",\n";
            payload += "\t\t\t" + JsonItem("Items", inventoryCounts[i].m_items);
            if (i == inventoryCounts.size() - 1) { payload += "\t\t}\n"; }
            else { payload += "\t\t},\n"; }
        }
        payload += "\t]\n}";
        return payload;
    }

    InvIO::InvIO() {}

    void InvIO::ExportToExcel(std::vector<Category>& inventory, const std::string& fileName, const std::string& filePath) {
        std::fstream baseTable;
        std::fstream newTable;
        baseTable.open("baseTable.xml", std::ios::in);
        newTable.open(filePath + "\\" + fileName + ".xml", std::ios::out);
        if (baseTable.is_open() && newTable.is_open()) {
            std::string line;
            while (std::getline(baseTable, line)) {
                if (line.find("</ss:Row>") != std::string::npos) {
                    newTable << line << "\n";
                    newTable << ExcelPayload(inventory);
                    break;
                }
            }
            newTable << line << "\n";
            baseTable.close();
            newTable.close();
        }
    }

    void InvIO::ExportToJSON(const std::vector<Category>& inventoryList, const std::vector<Count>& inventoryCounts) {
        std::fstream newJson;
        newJson.open("inventory.json", std::ios::out);
        newJson << JsonInventory(inventoryList, inventoryCounts);
        newJson.close();
    }

    std::vector<Category> InvIO::FromJSONInventory(const std::string& rawJson) {
        Parser parser;
        JSONObject parsedJSON = parser.Parse(rawJson);
        std::vector<Category> inventoryList;

        for (int i = 0; i < parsedJSON["Inventory"].mCount; i++) {
            std::string name = parsedJSON["Inventory"][i]["Name"].asString();
            std::string id = parsedJSON["Inventory"][i]["ID"].asString();
            int cost = parsedJSON["Inventory"][i]["Cost"].asInt();

            Category category(name.c_str(), id.c_str(), cost);

            for (int j = 0; j < parsedJSON["Inventory"][i]["Items"].mCount; j++) {
                std::string item_id = parsedJSON["Inventory"][i]["Items"][j]["ID"].asString();
                std::string item_uuid = parsedJSON["Inventory"][i]["Items"][j]["UUID"].asString();
                std::string item_parent = parsedJSON["Inventory"][i]["Items"][j]["Parent Category"].asString();
                std::string item_status = parsedJSON["Inventory"][i]["Items"][j]["Status"].asString();
                std::string item_lastCounted = parsedJSON["Inventory"][i]["Items"][j]["Last Counted"].asString();
                std::string item_dateAdded = parsedJSON["Inventory"][i]["Items"][j]["Date Added"].asString();

                Item item;
                item.SetId(item_id);
                item.SetUUID(item_uuid);
                item.SetParent(item_parent);
                item.SetStatus(item_status.c_str());
                item.SetLastCounted(item_lastCounted);
                item.SetDateAdded(item_dateAdded);

                category.PushItem(item);
            }
            inventoryList.push_back(category);
        }
        return inventoryList;
    }

    std::vector<Count> InvIO::FromJSONCounts(const std::string& rawJson) {
        Parser parser;
        JSONObject parsedJSON = parser.Parse(rawJson);
        std::vector<Count> inventoryCounts;

        for (int i = 0; i < parsedJSON["Counts"].mCount; i++) {
            std::string dateOpened = parsedJSON["Counts"][i]["Date Opened"].asString();
            std::string dateClosed = parsedJSON["Counts"][i]["Date Closed"].asString();
            int total = parsedJSON["Counts"][i]["Total"].asInt();
            int counted = parsedJSON["Counts"][i]["Counted"].asInt();
            int variance = parsedJSON["Counts"][i]["Variance"].asInt();
            int finished = parsedJSON["Counts"][i]["Finished"].asBool();

            Count count;
            count.m_dateOpened = dateOpened;
            count.m_dateClosed = dateClosed;
            count.m_total = total;
            count.m_counted = counted;
            count.m_variance = variance;
            count.m_finished = finished;

            for (int j = 0; j < parsedJSON["Counts"][i]["Items"].mCount; j++) {
                std::string item_id = parsedJSON["Counts"][i]["Items"][j]["ID"].asString();
                std::string item_uuid = parsedJSON["Counts"][i]["Items"][j]["UUID"].asString();
                std::string item_parent = parsedJSON["Counts"][i]["Items"][j]["Parent Category"].asString();
                std::string item_status = parsedJSON["Counts"][i]["Items"][j]["Status"].asString();
                std::string item_lastCounted = parsedJSON["Counts"][i]["Items"][j]["Last Counted"].asString();
                std::string item_dateAdded = parsedJSON["Counts"][i]["Items"][j]["Date Added"].asString();

                Item item;
                item.SetId(item_id);
                item.SetUUID(item_uuid);
                item.SetParent(item_parent);
                item.SetStatus(item_status.c_str());
                item.SetLastCounted(item_lastCounted);
                item.SetDateAdded(item_dateAdded);

                count.m_items.emplace_back(item);
            }
            inventoryCounts.emplace_back(count);
        }
        return inventoryCounts;
    }
}