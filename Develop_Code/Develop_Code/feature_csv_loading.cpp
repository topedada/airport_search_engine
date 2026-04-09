#include "LoadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>

// ---------------- Load CSV Implementation ----------------
void loadCSV(const std::string& filename, std::vector<Airport>& airports) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << "\n";
        return;
    }

    std::string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        getline(ss, token, ','); // ident
        getline(ss, a.type, ',');
        getline(ss, a.name, ',');
        getline(ss, token, ','); // elevation

        // Safe conversion for elevation
        try {
            a.elevation = token.empty() ? 0 : std::stoi(token);
        }
        catch (...) {
            a.elevation = 0;
        }

        getline(ss, token, ','); // continent
        getline(ss, a.country, ',');
        getline(ss, token, ','); // region
        getline(ss, a.municipality, ',');
        getline(ss, token, ','); // icao
        getline(ss, a.iata, ',');
        getline(ss, token, ','); // gps
        getline(ss, token, ','); // local
        getline(ss, token);       // coordinates

        // Remove surrounding quotes
        if (!token.empty() && token.front() == '"') token.erase(0, 1);
        if (!token.empty() && token.back() == '"') token.pop_back();

        // Safe conversion for coordinates
        std::stringstream coord(token);
        std::string lat, lon;
        getline(coord, lat, ',');
        getline(coord, lon, ',');

        try {
            a.latitude = lat.empty() ? 0.0 : std::stod(lat);
        }
        catch (...) {
            a.latitude = 0.0;
        }

        try {
            a.longitude = lon.empty() ? 0.0 : std::stod(lon);
        }
        catch (...) {
            a.longitude = 0.0;
        }

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// ---------------- Print Function ----------------
void printAirport(const Airport& a) {
    std::cout << "Name: " << a.name << "\n";
    std::cout << "Country: " << a.country << "\n";
    std::cout << "IATA: " << a.iata << "\n";
    std::cout << "Type: " << a.type << "\n";
    std::cout << "Municipality: " << a.municipality << "\n";
    std::cout << "Lat: " << a.latitude << ", Lon: " << a.longitude << "\n";
    std::cout << "Elevation: " << a.elevation << "\n";
    std::cout << "----------------------\n";
}

// ---------------- Search Functions ----------------
void searchByCountry(const std::vector<Airport>& airports, const std::string& countryCode) {
    int count = 0;
    for (const auto& a : airports) {
        if (toLower(a.country) == toLower(countryCode)) {
            printAirport(a);
            if (++count >= 10) break;
        }
    }
    if (count == 0) std::cout << "No airports found.\n";
}

void searchByName(const std::vector<Airport>& airports, const std::string& name) {
    int count = 0;
    for (const auto& a : airports) {
        if (toLower(a.name).find(toLower(name)) != std::string::npos) {
            printAirport(a);
            if (++count >= 10) break;
        }
    }
    if (count == 0) std::cout << "No airports found.\n";
}

void searchByIATA(const std::vector<Airport>& airports, const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) {
            printAirport(a);
            return;
        }
    }
    std::cout << "No airport found.\n";
}