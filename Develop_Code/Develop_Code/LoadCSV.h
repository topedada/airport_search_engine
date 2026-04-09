#pragma once
#include <string>
#include <vector>
#include <iostream>

// ---------------- Airport Struct ----------------
struct Airport {
    std::string name;
    std::string country;
    std::string iata;
    std::string type;
    std::string municipality;
    double latitude;
    double longitude;
    int elevation;
};

// ---------------- Inline Helper ----------------
inline std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = tolower(c);
    return result;
}

// ---------------- Load CSV Function ----------------
void loadCSV(const std::string& filename, std::vector<Airport>& airports);

// ---------------- Search Functions ----------------
void searchByCountry(const std::vector<Airport>& airports, const std::string& countryCode);
void searchByName(const std::vector<Airport>& airports, const std::string& name);
void searchByIATA(const std::vector<Airport>& airports, const std::string& code);
void printAirport(const Airport& a);