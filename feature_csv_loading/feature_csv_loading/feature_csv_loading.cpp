#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Airport.h"  // Use your header file

// ---------------- Helpers ----------------
std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = tolower(c);
    return result;
}

double toDouble(const std::string& s) {
    try { return std::stod(s); }
    catch (...) { return 0.0; }
}

int toInt(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return 0; }
}

// ---------------- Load CSV ----------------
void loadCSV(const std::string& filename, std::vector<Airport>& airports) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << "\n";
        return;
    }

    std::string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        getline(ss, token, ',');         // ident
        getline(ss, a.type, ',');        // type
        getline(ss, a.name, ',');        // name

        getline(ss, token, ',');         // elevation
        a.elevation = toInt(token);

        getline(ss, token, ',');         // continent
        getline(ss, a.country, ',');     // country

        getline(ss, token, ',');         // region
        getline(ss, a.municipality, ',');// municipality

        getline(ss, token, ',');         // icao
        getline(ss, a.iata, ',');        // iata_code

        getline(ss, token, ',');         // gps_code
        getline(ss, token, ',');         // local_code

        getline(ss, token);               // coordinates
        if (!token.empty() && token.front() == '"') token.erase(0, 1);
        if (!token.empty() && token.back() == '"') token.pop_back();

        std::stringstream coord(token);
        std::string lat, lon;
        getline(coord, lat, ',');
        getline(coord, lon, ',');

        a.latitude = toDouble(lat);
        a.longitude = toDouble(lon);

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// ---------------- Print ----------------
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

// ---------------- Main ----------------
int main() {
    std::vector<Airport> airports;
    loadCSV("airports.csv", airports); // assumes CSV is in same folder as exe

    // Just print first 10 airports for testing
    int count = 0;
    for (const auto& a : airports) {
        printAirport(a);
        if (++count >= 10) break;
    }

    return 0;
}