#pragma once
#include <vector>
#include <string>
#include "Airport.h"

void adminAirportMenu(std::vector<Airport>& airports);
void saveCSV(const std::string& filename, const std::vector<Airport>& airports);

int getIntInput(const std::string& prompt);
double getDoubleInput(const std::string& prompt);