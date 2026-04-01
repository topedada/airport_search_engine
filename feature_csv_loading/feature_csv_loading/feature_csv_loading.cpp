#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem> // For debug absolute path

// -------- Airport Struct --------
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

std::vector<Airport> airports;

// -------- Helper Conversion Functions --------
double toDouble(const std::string& s) {
    try { return std::stod(s); }
    catch (...) { return 0.0; }
}

int toInt(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return 0; }
}

// -------- Load CSV Function --------
void loadCSV(const std::string& filename) {
    std::cout << "Trying to open CSV file at: "
        << std::filesystem::absolute(filename) << "\n";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file: " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        getline(ss, token, ','); // 1 ident, ignore
        getline(ss, a.type, ','); // 2 type
        getline(ss, a.name, ','); // 3 name
        getline(ss, token, ',');
        a.elevation = toInt(token); // 4 elevation_ft
        getline(ss, token, ','); // 5 continent, ignore
        getline(ss, a.country, ','); // 6 iso_country
        getline(ss, token, ','); // 7 iso_region, ignore
        getline(ss, a.municipality, ','); // 8 municipality
        getline(ss, token, ','); // 9 icao_code, ignore
        getline(ss, a.iata, ','); // 10 iata_code
        getline(ss, token, ','); // 11 gps_code, ignore
        getline(ss, token, ','); // 12 local_code, ignore
        getline(ss, token, ','); // 13 coordinates

        // Split coordinates into latitude and longitude
        std::stringstream coord(token);
        std::string latStr, lonStr;
        getline(coord, latStr, ' '); // space-separated
        getline(coord, lonStr, ' ');
        a.latitude = toDouble(latStr);
        a.longitude = toDouble(lonStr);

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// -------- Debug Print Function --------
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

// -------- Search Functions --------
void searchByCountry(const std::string& countryCode) {
    std::cout << "Airports in country: " << countryCode << "\n";
    for (const auto& a : airports) {
        if (a.country == countryCode) printAirport(a);
    }
}

void searchByName(const std::string& partialName) {
    std::cout << "Airports matching name: " << partialName << "\n";
    for (const auto& a : airports) {
        if (a.name.find(partialName) != std::string::npos) printAirport(a);
    }
}

void searchByIATA(const std::string& code) {
    std::cout << "Airport with IATA code: " << code << "\n";
    for (const auto& a : airports) {
        if (a.iata == code) printAirport(a);
    }
}

// -------- Main Function --------
int main() {
    std::string csvPath = "../../data/airports.csv";
    loadCSV(csvPath);

    // Test searches
    searchByCountry("US");       // Example: United States
    searchByName("Heathrow");    // Example: partial name
    searchByIATA("LHR");         // Example: IATA code

    return 0;
}