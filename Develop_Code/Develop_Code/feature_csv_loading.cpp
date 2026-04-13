#include "LoadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// ================= LOWERCASE HELP =================
std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string normaliseType(std::string s) {

    std::string result;

    for (char c : s) {

        if (c == '_' || c == '-' || c == ' ') {
            result += ' ';
        }
        else {
            result += std::tolower(c);
        }
    }

    return result;
}

void countAirportTypes(const std::vector<Airport>& airports) {

    int large = 0;
    int small = 0;
    int heliport = 0;

    for (const auto& a : airports) {

        std::string type = normaliseType(a.type);

        if (type.find("large") != std::string::npos) {
            large++;
        }
        else if (type.find("small") != std::string::npos) {
            small++;
        }
        else if (type.find("heliport") != std::string::npos) {
            heliport++;
        }
    }

    std::cout << "\n===== AIRPORT TYPE COUNT =====\n";
    std::cout << "Large Airports: " << large << "\n";
    std::cout << "Small Airports: " << small << "\n";
    std::cout << "Heliports: " << heliport << "\n";
}

// ================= LOAD CSV =================
void loadCSV(const std::string& filename, std::vector<Airport>& airports) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening CSV file\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {

        std::stringstream ss(line);
        Airport a;

        std::string elevationStr;
        std::string coordinates;

        std::getline(ss, a.ident, ',');
        std::getline(ss, a.type, ',');
        std::getline(ss, a.name, ',');
        std::getline(ss, elevationStr, ',');
        std::getline(ss, a.continent, ',');
        std::getline(ss, a.iso_country, ',');
        std::getline(ss, a.iso_region, ',');
        std::getline(ss, a.municipality, ',');
        std::getline(ss, a.icao, ',');
        std::getline(ss, a.iata, ',');
        std::getline(ss, a.gps, ',');
        std::getline(ss, a.local, ',');
        std::getline(ss, coordinates);

        try {
            a.elevation = std::stod(elevationStr);
        }
        catch (...) {
            a.elevation = 0;
        }

        coordinates.erase(std::remove(coordinates.begin(), coordinates.end(), '\"'), coordinates.end());

        size_t pos = coordinates.find(',');

        if (pos != std::string::npos) {
            try {
                a.latitude = std::stod(coordinates.substr(0, pos));
                a.longitude = std::stod(coordinates.substr(pos + 1));
            }
            catch (...) {
                a.latitude = 0;
                a.longitude = 0;
            }
        }
        else {
            a.latitude = 0;
            a.longitude = 0;
        }

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports\n";
}

// ================= SEARCH BY NAME (CASE INSENSITIVE) =================
void searchByName(const std::vector<Airport>& airports, const std::string& input) {

    bool found = false;

    for (const auto& a : airports) {

        if (toLower(a.name).find(toLower(input)) != std::string::npos) {

            std::cout << "\n--- AIRPORT FOUND ---\n";
            std::cout << "Name: " << a.name << "\n";
            std::cout << "Ident: " << a.ident << "\n";
            std::cout << "Type: " << a.type << "\n";
            std::cout << "Elevation: " << a.elevation << "\n";
            std::cout << "Continent: " << a.continent << "\n";
            std::cout << "Country: " << a.iso_country << "\n";
            std::cout << "Region: " << a.iso_region << "\n";
            std::cout << "Municipality: " << a.municipality << "\n";
            std::cout << "ICAO: " << a.icao << "\n";
            std::cout << "IATA: " << a.iata << "\n";
            std::cout << "GPS: " << a.gps << "\n";
            std::cout << "Local: " << a.local << "\n";
            std::cout << "Latitude: " << a.latitude << "\n";
            std::cout << "Longitude: " << a.longitude << "\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "No airport found\n";
    }
}

// ================= SEARCH BY IATA (CASE INSENSITIVE) =================
void searchByIATA(const std::vector<Airport>& airports, const std::string& input) {

    bool found = false;

    for (const auto& a : airports) {

        if (toLower(a.iata) == toLower(input)) {

            std::cout << "\n--- AIRPORT FOUND ---\n";
            std::cout << "Name: " << a.name << "\n";
            std::cout << "Ident: " << a.ident << "\n";
            std::cout << "Type: " << a.type << "\n";
            std::cout << "Elevation: " << a.elevation << "\n";
            std::cout << "Country: " << a.iso_country << "\n";
            std::cout << "Region: " << a.iso_region << "\n";
            std::cout << "ICAO: " << a.icao << "\n";
            std::cout << "IATA: " << a.iata << "\n";
            std::cout << "Latitude: " << a.latitude << "\n";
            std::cout << "Longitude: " << a.longitude << "\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "No airport found\n";
    }
}

// ================= SEARCH BY COUNTRY (CASE INSENSITIVE) =================
void searchByCountry(const std::vector<Airport>& airports, const std::string& input) {

    bool found = false;

    for (const auto& a : airports) {

        if (toLower(a.iso_country) == toLower(input)) {

            std::cout << "\n--- AIRPORT FOUND ---\n";
            std::cout << "Name: " << a.name << "\n";
            std::cout << "Ident: " << a.ident << "\n";
            std::cout << "Type: " << a.type << "\n";
            std::cout << "Elevation: " << a.elevation << "\n";
            std::cout << "Country: " << a.iso_country << "\n";
            std::cout << "Region: " << a.iso_region << "\n";
            std::cout << "ICAO: " << a.icao << "\n";
            std::cout << "IATA: " << a.iata << "\n";
            std::cout << "Latitude: " << a.latitude << "\n";
            std::cout << "Longitude: " << a.longitude << "\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "No airports found in this country\n";
    }
}