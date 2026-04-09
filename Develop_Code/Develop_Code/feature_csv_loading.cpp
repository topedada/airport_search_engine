#include "LoadCSV.h"
#include <fstream>
#include <sstream>
#include <limits>

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

        getline(ss, token, ',');
        a.elevation = toInt(token);

        getline(ss, token, ','); // continent
        getline(ss, a.country, ',');

        getline(ss, token, ','); // region
        getline(ss, a.municipality, ',');

        getline(ss, token, ','); // icao
        getline(ss, a.iata, ',');

        getline(ss, token, ','); // gps
        getline(ss, token, ','); // local

        getline(ss, token);
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

// ---------------- Search Functions ----------------
void searchByCountry(const std::vector<Airport>& airports, const std::string& countryCode) {
    int count = 0;
    for (const auto& a : airports) {
        if (toLower(a.country) == toLower(countryCode)) {
            printAirport(a);
            count++;
            if (count >= 10) break;
        }
    }
    if (count == 0) std::cout << "No airports found.\n";
}

void searchByName(const std::vector<Airport>& airports, const std::string& name) {
    int count = 0;
    for (const auto& a : airports) {
        if (toLower(a.name).find(toLower(name)) != std::string::npos) {
            printAirport(a);
            count++;
            if (count >= 10) break;
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