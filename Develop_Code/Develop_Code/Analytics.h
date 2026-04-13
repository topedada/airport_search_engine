#pragma once
#include <vector>
#include "LoadCSV.h"

void advancedMenu(std::vector<Airport>& airports);
void findNearestAirport(const std::vector<Airport>& airports);
void airportsWithinRadius(const std::vector<Airport>& airports);
void elevationStats(const std::vector<Airport>& airports);
void missingIATACodes(const std::vector<Airport>& airports);
void printAirport(const Airport& a);