#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

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

// -------- Helpers --------
double toDouble(const std::string& s) {
    try { return std::stod(s); }
    catch (...) { return 0.0; }
}

int toInt(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return 0; }
}

// -------- Load CSV --------
void loadCSV(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file.\n";
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
        getline(ss, token, ','); // coordinates

        // split coordinates
        std::stringstream coord(token);
        std::string lat, lon;
        getline(coord, lat, ' ');
        getline(coord, lon, ' ');

        a.latitude = toDouble(lat);
        a.longitude = toDouble(lon);

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// -------- Print --------
void printAirport(const Airport& a) {
    std::cout << a.name << " (" << a.iata << ") - "
        << a.country << " - " << a.type << "\n";
}

// -------- Search Functions --------
void searchByCountry(const std::string& countryCode) {
    bool found = false;
    int count = 0;

    for (const auto& a : airports) {
        if (a.country == countryCode) {
            printAirport(a);
            found = true;
            count++;
            if (count >= 10) break;
        }
    }

    if (!found) std::cout << "No airports found.\n";
}

void searchByName(const std::string& name) {
    bool found = false;
    int count = 0;

    for (const auto& a : airports) {
        if (a.name.find(name) != std::string::npos) {
            printAirport(a);
            found = true;
            count++;
            if (count >= 10) break;
        }
    }

    if (!found) std::cout << "No airports found.\n";
}

void searchByIATA(const std::string& code) {
    bool found = false;

    for (const auto& a : airports) {
        if (a.iata == code) {
            printAirport(a);
            found = true;
            break;
        }
    }

    if (!found) std::cout << "No airport found.\n";
}

// -------- Main Menu --------
int main() {
    loadCSV("../../data/airports.csv");

    int choice;
    std::string input;

    while (true) {
        std::cout << "\n--- Airport Menu ---\n";
        std::cout << "1. Search by Country\n";
        std::cout << "2. Search by Name\n";
        std::cout << "3. Search by IATA\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 4) break;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter search: ";
        getline(std::cin, input);

        if (choice == 1) searchByCountry(input);
        else if (choice == 2) searchByName(input);
        else if (choice == 3) searchByIATA(input);
        else std::cout << "Invalid option\n";
    }

    return 0;
}