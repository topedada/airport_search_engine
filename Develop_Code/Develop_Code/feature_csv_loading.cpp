#include "LoadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Define the airports vector
std::vector<Airport> airports;

// Helpers
int toInt(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return 0; }
}

double toDouble(const std::string& s) {
    try { return std::stod(s); }
    catch (...) { return 0.0; }
}

// Load CSV function
void loadCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open " << filename << "\n";
        return;
    }

    std::string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        // Skip first 9 columns to reach IATA code (column J, index 9)
        for (int i = 0; i < 9; i++) getline(ss, token, ',');

        getline(ss, a.iata, ','); // column J: iata_code

        // Optional: initialize other fields as empty
        a.name = ""; a.country = ""; a.type = ""; a.municipality = "";
        a.latitude = 0; a.longitude = 0; a.elevation = 0;

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}