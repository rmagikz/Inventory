#include "Utility.h"

namespace SimpleInventory {
	std::string AssignID(int count) { return std::to_string(count + 10000); }

    Timer::Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    Timer::~Timer() {
        std::chrono::duration<float> duration = std::chrono::high_resolution_clock::now() - start;
        std::cout << "duration: " << duration.count() * 1000 << "ms\n";
    }
}