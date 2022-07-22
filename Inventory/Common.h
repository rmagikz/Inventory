#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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