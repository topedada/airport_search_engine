#include <iostream>
#include <vector>
#include <string>
#include "LoadCSV.h"

// -------- Admin Functions --------
void addAirport(std::vector<Airport>& airports) {
    Airport a;

    std::cout << "Enter airport name: ";
    std::getline(std::cin, a.name);

    std::cout << "Enter country code: ";
    std::getline(std::cin, a.country);

    std::cout << "Enter IATA code: ";
    std::getline(std::cin, a.iata);

    std::cout << "Enter type: ";
    std::getline(std::cin, a.type);

    std::cout << "Enter municipality: ";
    std::getline(std::cin, a.municipality);

    std::cout << "Enter latitude: ";
    std::cin >> a.latitude;

    std::cout << "Enter longitude: ";
    std::cin >> a.longitude;

    std::cout << "Enter elevation: ";
    std::cin >> a.elevation;
    std::cin.ignore();

    airports.push_back(a);

    std::cout << "Airport added successfully!\n";
}

// ------------------------------
void viewAirports(const std::vector<Airport>& airports) {
    if (airports.empty()) {
        std::cout << "No airports available.\n";
        return;
    }

    int count = 0;
    for (const auto& a : airports) {
        printAirport(a);
        if (++count >= 10) break; // limit to 10
    }
}

// ------------------------------
void deleteAirport(std::vector<Airport>& airports) {
    std::string code;

    std::cout << "Enter IATA code of airport to delete: ";
    std::getline(std::cin, code);

    for (auto it = airports.begin(); it != airports.end(); ++it) {
        if (toLower(it->iata) == toLower(code)) {
            airports.erase(it);
            std::cout << "Airport deleted.\n";
            return;
        }
    }

    std::cout << "Airport not found.\n";
}

// ------------------------------
void adminMenu(std::vector<Airport>& airports) {
    int choice;

    while (true) {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. Add Airport\n";
        std::cout << "2. View Airports\n";
        std::cout << "3. Delete Airport\n";
        std::cout << "4. Back\n";
        std::cout << "Choice: ";

        std::cin >> choice;
        std::cin.ignore();

        if (choice == 4) break;

        switch (choice) {
        case 1:
            addAirport(airports);
            break;
        case 2:
            viewAirports(airports);
            break;
        case 3:
            deleteAirport(airports);
            break;
        default:
            std::cout << "Invalid option\n";
        }
    }
}

// -------- MAIN (FOR TESTING) --------
int main() {
    std::vector<Airport> airports;

    loadCSV("../../data/airports.csv", airports);

    if (airports.empty()) {
        std::cout << "No airports loaded.\n";
        return 1;
    }

    adminMenu(airports);

    std::cout << "Exiting Admin System.\n";
    return 0;
}