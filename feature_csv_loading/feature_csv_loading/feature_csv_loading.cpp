#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem> // For absolute path debug

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

double toDouble(const std::string& s) {
    try { return std::stod(s); }
    catch (...) { return 0.0; }
}

int toInt(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return 0; }
}

void loadCSV(const std::string& filename) {
    std::cout << "Trying to open CSV file at: "
        << std::filesystem::absolute(filename) << "\n";

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: Could not open file: " << filename << "\n";
        std::cout << "Make sure the file exists and is fully local.\n";
        return;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        std::getline(ss, a.name, ',');
        std::getline(ss, a.country, ',');
        std::getline(ss, a.iata, ',');
        std::getline(ss, a.type, ',');
        std::getline(ss, a.municipality, ',');

        std::getline(ss, token, ',');
        a.latitude = toDouble(token);

        std::getline(ss, token, ',');
        a.longitude = toDouble(token);

        std::getline(ss, token, ',');
        a.elevation = toInt(token);

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

void printSample(int count = 5) {
    for (int i = 0; i < count && i < airports.size(); i++) {
        std::cout << "Name: " << airports[i].name << "\n";
        std::cout << "Country: " << airports[i].country << "\n";
        std::cout << "IATA: " << airports[i].iata << "\n";
        std::cout << "Type: " << airports[i].type << "\n";
        std::cout << "Municipality: " << airports[i].municipality << "\n";
        std::cout << "Lat: " << airports[i].latitude
            << ", Lon: " << airports[i].longitude << "\n";
        std::cout << "Elevation: " << airports[i].elevation << "\n";
        std::cout << "----------------------\n";
    }
}

int main() {
    std::string csvPath = "../../data/airports.csv";
    loadCSV(csvPath);
    printSample();
    return 0;
}