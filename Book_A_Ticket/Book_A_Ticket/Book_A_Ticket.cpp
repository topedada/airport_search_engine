#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Airport.h"  // include the same header

// ---------------- Load CSV ----------------
void loadCSV(const std::string& filename, std::vector<Airport>& airports) {
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

        // Skip first 9 columns to reach iata_code (column J, index 9)
        for (int i = 0; i < 9; i++) getline(ss, token, ',');

        getline(ss, a.iata, ','); // column J: iata_code

        // Optionally store name, country, type, etc.
        a.name = ""; a.country = ""; a.type = ""; a.municipality = "";
        a.latitude = 0; a.longitude = 0; a.elevation = 0;

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}