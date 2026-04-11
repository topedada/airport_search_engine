#pragma once
#include <vector>
#include <string>
#include "Airport.h"
#include <iostream>

inline std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = tolower(c);
    return result;
}

int generateIdent(const std::vector<Airport>& airports);

void loadCSV(const std::string& filename, std::vector<Airport>& airports);
void printAirport(const Airport& a);
void searchByCountry(const std::vector<Airport>& airports, const std::string& countryCode);
void searchByName(const std::vector<Airport>& airports, const std::string& name);
void searchByIATA(const std::vector<Airport>& airports, const std::string& code);