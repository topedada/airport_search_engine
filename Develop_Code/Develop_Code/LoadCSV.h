#pragma once
#include <string>
#include <vector>
#include "Airport.h"

// Declare the global airports vector
extern std::vector<Airport> airports;

// Function declarations
void loadCSV(const std::string& filename);
int toInt(const std::string& s);
double toDouble(const std::string& s);