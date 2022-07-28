#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include <cstdint>
#include <iostream>
#include <vector>
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

std::string AssignID(int count) { return std::to_string(count + 10000); }

void GetInput(std::string& buff) { std::getline(std::cin, buff); }

struct Timer {
    std::chrono::steady_clock::time_point start;

    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Timer() {
        std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start;
        std::cout << "DURATION: " << duration.count() * 1000 << "ms\n";
    }
};