#pragma once

#include "Common.h"

using namespace DYMO_Label_Framework;

void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print) {
    std::fstream baseLabel;
    std::fstream newLabel;
    baseLabel.open("baseLabel.label", std::ios::in);
    newLabel.open("newLabel.label", std::ios::out);
    std::string line;
    if (baseLabel.is_open()) {
        while (std::getline(baseLabel, line)) {
            if (line.find("<Text>") != std::string::npos) {
                newLabel << "              <Text>" << categoryId << "-" << itemId << "</Text>\n";
            }
            else if (line.find("<String") != std::string::npos) {
                newLabel << "                   <String xml:space=\"preserve\">" << catName << "</String>\n";
            }
            else { newLabel << line << "\n"; }
        }
        newLabel.close();
        baseLabel.close();
    }

    std::cout << catName << std::endl;
    std::cout << "ID: " << categoryId << "-" << itemId << std::endl;
    std::cout << std::endl;

    if (print == 1) {
        std::cout << "PRINTING LABEL" << std::endl;
        try
        {
            IFrameworkPtr framework(__uuidof(Framework));
            ILabelPtr label = framework->OpenLabel(L"newLabel.label");
            framework->PrintLabel(L"DYMO LabelWriter 450 Turbo", L"", label->SaveToXml(), L"");
        }
        catch (_com_error& e)
        {
            _tprintf_s(_T("Com error was \"%s\", HRESULT 0x%X\n"), e.ErrorMessage(), e.Error());
        }
    }
}