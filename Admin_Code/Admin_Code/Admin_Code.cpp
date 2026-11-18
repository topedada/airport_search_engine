#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// ---------------- Airport Struct ----------------
struct Airport {
    std::string ident;
    std::string type;
    std::string name;
    std::string elevation_ft;
    std::string continent;
    std::string iso_country;
    std::string iso_region;
    std::string municipality;
    std::string icao_code;
    std::string iata_code;
    std::string gps_code;
    std::string local_code;
    std::string coordinates;
};

// ---------------- LOAD CSV ----------------
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
        Airport a;

        getline(ss, a.ident, ',');
        getline(ss, a.type, ',');
        getline(ss, a.name, ',');
        getline(ss, a.elevation_ft, ',');
        getline(ss, a.continent, ',');
        getline(ss, a.iso_country, ',');
        getline(ss, a.iso_region, ',');
        getline(ss, a.municipality, ',');
        getline(ss, a.icao_code, ',');
        getline(ss, a.iata_code, ',');
        getline(ss, a.gps_code, ',');
        getline(ss, a.local_code, ',');
        getline(ss, a.coordinates);

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// ---------------- SAVE CSV ----------------
void saveCSV(const std::string& filename, const std::vector<Airport>& airports) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error saving file.\n";
        return;
    }

    file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao_code,iata_code,gps_code,local_code,coordinates\n";

    for (const auto& a : airports) {
        file << a.ident << ","
            << a.type << ","
            << a.name << ","
            << a.elevation_ft << ","
            << a.continent << ","
            << a.iso_country << ","
            << a.iso_region << ","
            << a.municipality << ","
            << a.icao_code << ","
            << a.iata_code << ","
            << a.gps_code << ","
            << a.local_code << ","
            << a.coordinates << "\n";
    }

    std::cout << "Saved successfully.\n";
}

// ---------------- VIEW ----------------
void viewAirports(const std::vector<Airport>& airports) {
    for (const auto& a : airports) {
        std::cout << a.name << " (" << a.iata_code << ") - "
            << a.iso_country << "\n";
    }
}

// ---------------- ADD ----------------
void addAirport(std::vector<Airport>& airports) {
    Airport a;

    std::cout << "ident: "; getline(std::cin, a.ident);
    std::cout << "type: "; getline(std::cin, a.type);
    std::cout << "name: "; getline(std::cin, a.name);
    std::cout << "elevation_ft: "; getline(std::cin, a.elevation_ft);
    std::cout << "continent: "; getline(std::cin, a.continent);
    std::cout << "iso_country: "; getline(std::cin, a.iso_country);
    std::cout << "iso_region: "; getline(std::cin, a.iso_region);
    std::cout << "municipality: "; getline(std::cin, a.municipality);
    std::cout << "icao_code: "; getline(std::cin, a.icao_code);
    std::cout << "iata_code: "; getline(std::cin, a.iata_code);
    std::cout << "gps_code: "; getline(std::cin, a.gps_code);
    std::cout << "local_code: "; getline(std::cin, a.local_code);
    std::cout << "coordinates: "; getline(std::cin, a.coordinates);

    airports.push_back(a);

    std::cout << "Airport added.\n";
}

// ---------------- DELETE ----------------
void deleteAirport(std::vector<Airport>& airports) {
    std::string code;

    std::cout << "Enter IATA code to delete: ";
    std::getline(std::cin, code);

    for (int i = 0; i < airports.size(); i++) {
        if (airports[i].iata_code == code) {
            airports.erase(airports.begin() + i);
            std::cout << "Airport deleted.\n";
            return;
        }
    }

    std::cout << "Airport not found.\n";
}

// ---------------- MAIN MENU ----------------
int main() {
    std::vector<Airport> airports;

    loadCSV("../../data/airports_test.csv", airports);

    int choice;

    while (true) {
        std::cout << "\n--- ADMIN AIRPORT SYSTEM ---\n";
        std::cout << "1. View Airports\n";
        std::cout << "2. Add Airport\n";
        std::cout << "3. Delete Airport\n";
        std::cout << "4. Save Changes\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            viewAirports(airports);
        }
        else if (choice == 2) {
            addAirport(airports);
        }
        else if (choice == 3) {
            deleteAirport(airports);
        }
        else if (choice == 4) {
            saveCSV("../../data/airports_test.csv", airports);
        }
        else if (choice == 5) {
            break;
        }
        else {
            std::cout << "Invalid option.\n";
        }
    }

    return 0;
}