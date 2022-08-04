#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

#include <cstdint>
#include <iostream>
#include <vector>

#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>
#include <atlpath.h>
#include <atlsafe.h>

#import "DYMO.Label.Framework.tlb" rename("CreateFont", "CreateFont_")

namespace SimpleInventory {

    using namespace DYMO_Label_Framework;

    void GenerateLabel(const int& categoryId, const int& itemId, std::string catName, const int& print);
}