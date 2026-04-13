#pragma once

#include <vector>
#include <string>
#include "Airport.h"

// ================= CSV =================
void loadCSV(const std::string& filename, std::vector<Airport>& airports);

void countAirportTypes(const std::vector<Airport>& airports);

// ================= HELPERS =================
std::string toLower(const std::string& s);

void searchByName(const std::vector<Airport>& airports, const std::string& input);
void searchByIATA(const std::vector<Airport>& airports, const std::string& input);
void searchByCountry(const std::vector<Airport>& airports, const std::string& input);