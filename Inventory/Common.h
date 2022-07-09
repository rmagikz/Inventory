#pragma once

#include <iostream>

void log(const char* message) {
	std::cout << message << std::endl;
}

std::string split(const std::string& str, const std::string& delimiter, const int& index = 0) {
	return str.substr(index, str.find(delimiter));
}