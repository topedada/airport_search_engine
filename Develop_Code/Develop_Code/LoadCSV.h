#pragma once
#include <iostream>
#include <vector>
#include <string>

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

// ---------------- LoadCSV Functions ----------------
void loadCSV(const std::string& filename, std::vector<Airport>& airports);
void printAirport(const Airport& a);
void searchByCountry(const std::vector<Airport>& airports, const std::string& countryCode);
void searchByName(const std::vector<Airport>& airports, const std::string& name);
void searchByIATA(const std::vector<Airport>& airports, const std::string& code);

// ---------------- Helpers ----------------
std::string toLower(const std::string& s);
double toDouble(const std::string& s);
int toInt(const std::string& s);