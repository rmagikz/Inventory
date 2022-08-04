#pragma once

#include <string>
#include <chrono>
#include <iostream>

namespace SimpleInventory {
	std::string AssignID(int count);

    struct Timer {
        std::chrono::steady_clock::time_point start;

        Timer();

        ~Timer();
    };
}