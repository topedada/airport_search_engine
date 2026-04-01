#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

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

// -------- Global Vector --------
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
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error: Could not open file: " << filename << "\n";
        return;
    }

    std::string line;

    // Skip header row
    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        Airport a;

        // Adjust order here to match your CSV!
        getline(ss, a.name, ',');
        getline(ss, a.country, ',');
        getline(ss, a.iata, ',');
        getline(ss, a.type, ',');
        getline(ss, a.municipality, ',');

        getline(ss, token, ',');
        a.latitude = toDouble(token);

        getline(ss, token, ',');
        a.longitude = toDouble(token);

        getline(ss, token, ',');
        a.elevation = toInt(token);

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// -------- Debug Print Function --------
void printSample(int count = 5) {
    for (int i = 0; i < count && i < airports.size(); i++) {
        std::cout << "Name: " << airports[i].name << "\n";
        std::cout << "Country: " << airports[i].country << "\n";
        std::cout << "IATA: " << airports[i].iata << "\n";
        std::cout << "Type: " << airports[i].type << "\n";
        std::cout << "Municipality: " << airports[i].municipality << "\n";
        std::cout << "Lat: " << airports[i].latitude << ", Lon: " << airports[i].longitude << "\n";
        std::cout << "Elevation: " << airports[i].elevation << "\n";
        std::cout << "----------------------\n";
    }
}

// -------- Main Function --------
int main() {
    
    loadCSV("../data/airports");

    // Print first 5 airports to check
    printSample();

    return 0;
}