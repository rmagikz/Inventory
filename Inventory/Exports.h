#pragma once

#include "Common.h"
#include "Category.h"

using namespace std::string_literals;

class Exports {
private:
    std::string ExportLine(const std::string& content = "", const std::string& type = "String") {
        return "<ss:Cell><ss:Data ss:Type=\"" + type + "\">" + content + "</ss:Data></ss:Cell>\n";
    }

    void LoadCategory(std::string& payload, Category& category) {
        payload
            += "<ss:Row>"
            + ExportLine(category.m_id, "Number")
            + ExportLine()
            + ExportLine(category.m_name)
            + ExportLine(std::to_string(category.m_cost), "Number")
            + ExportLine()
            + ExportLine()
            + "</ss:Row>";
    }

    void LoadItem(std::string& payload, Item& item) {
        payload
            += "<ss:Row>"
            + ExportLine()
            + ExportLine(item.m_id, "Number")
            + ExportLine()
            + ExportLine()
            + ExportLine(item.GetStatus())
            + ExportLine()
            + "</ss:Row>";
    }

    std::string ExcelPayload(std::vector<Category> inventoryList) {
        std::string payload;
        for (int i = 0; i < inventoryList.size(); i++) {
            LoadCategory(payload, inventoryList[i]);
            for (int j = 0; j < inventoryList[i].items.size(); j++) {
                LoadItem(payload, inventoryList[i].items[j]);
            }
            payload += "<ss:Row>" + ExportLine() + "</ss:Row>";
        }
        payload += "</ss:Table>";
        payload += "</ss:Worksheet>";
        payload += "</ss:Workbook>";
        return payload;
    }

    std::string ToJsonString(const std::string& string) {
        return "\"" + string + "\"";
    }

    std::string JsonNumber(const std::string& key, const int& value) {
        return ToJsonString(key) + " : " + std::to_string(value);
    }

    std::string JsonString(const std::string& key, const std::string& value) {
        return ToJsonString(key) + " : " + ToJsonString(value);
    }
    
    std::string JsonItem(const std::string& key, std::vector<Item>& items) {
        std::string result;
        result += ToJsonString(key) + " : [\n";
        for (int i = 0; i < items.size(); i++) {
            result += "\t\t\t\t{\n";
            result += "\t\t\t\t\t" + JsonString("ID", items[i].m_id) + ",\n";
            result += "\t\t\t\t\t" + JsonString("Status", items[i].GetStatus()) + "\n";
            if (i == items.size() - 1) { result += "\t\t\t\t}\n"; }
            else { result += "\t\t\t\t},\n"; }
        }
        result += "\t\t\t]\n";
        return result;
    }

    std::string JsonPayload(std::vector<Category>& inventoryList) {
        std::string payload;
        payload += "{\n";
        payload += "\t" + ToJsonString("Inventory") + " : [\n";
        for (int i = 0; i < inventoryList.size(); i++) {
            payload += "\t\t{\n";
            payload += "\t\t\t" + JsonString("Name", inventoryList[i].m_name) + ",\n";
            payload += "\t\t\t" +JsonString("ID", inventoryList[i].m_id) + ",\n";
            payload += "\t\t\t" + JsonNumber("Cost", inventoryList[i].m_cost) + ",\n";
            payload += "\t\t\t" + JsonItem("Items", inventoryList[i].items);
            if (i == inventoryList.size() -1) { payload += "\t\t}\n"; }
            else { payload += "\t\t},\n"; }
        }
        payload += "\t]\n}";
        return payload;
    }
public:
	Exports() {}

	void ExportToExcel(std::vector<Category>& inventory) {
        std::fstream baseTable;
        std::fstream newTable;
        baseTable.open("baseTable.xml", std::ios::in);
        newTable.open("newTable.xml", std::ios::out);
        if (baseTable.is_open() && newTable.is_open()) {
            std::string line;
            while (std::getline(baseTable, line)) {
                if (line.find("</ss:Row>") != std::string::npos) {
                    newTable << line << std::endl;
                    newTable << ExcelPayload(inventory);
                    break;
                }
            }
            newTable << line << std::endl;
            baseTable.close();
            newTable.close();
        }
	}

	void ExportToJSON(std::vector<Category>& inventory) {
        std::fstream newJson;
        newJson.open("inventory.json", std::ios::out);
        newJson << JsonPayload(inventory);
        newJson.close();
	}
};