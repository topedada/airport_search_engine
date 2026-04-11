#include "Admin.h"
#include <iostream>
#include <fstream>

// ---------------- SAVE CSV ----------------
void saveCSV(const std::string& filename, const std::vector<Airport>& airports) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file.\n";
        return;
    }

    file << "name,country,iata,type,municipality,latitude,longitude,elevation\n";

    for (const auto& a : airports) {
        file << a.name << ","
            << a.country << ","
            << a.iata << ","
            << a.type << ","
            << a.municipality << ","
            << a.latitude << ","
            << a.longitude << ","
            << a.elevation << "\n";
    }

    std::cout << "Saved successfully.\n";
}

// ---------------- ADMIN MENU ----------------
void adminAirportMenu(std::vector<Airport>& airports) {
    int choice;

    while (true) {
        std::cout << "\n--- ADMIN MENU ---\n";
        std::cout << "1. Add Airport\n";
        std::cout << "2. Delete Airport\n";
        std::cout << "3. Save\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;
        std::cin.ignore();

        // -------- ADD --------
        if (choice == 1) {
            Airport a;

            std::cout << "Name: ";
            std::getline(std::cin, a.name);

            std::cout << "Country: ";
            std::getline(std::cin, a.country);

            std::cout << "IATA: ";
            std::getline(std::cin, a.iata);

            std::cout << "Type: ";
            std::getline(std::cin, a.type);

            std::cout << "Municipality: ";
            std::getline(std::cin, a.municipality);

            std::cout << "Latitude: ";
            std::cin >> a.latitude;

            std::cout << "Longitude: ";
            std::cin >> a.longitude;

            std::cout << "Elevation: ";
            std::cin >> a.elevation;

            std::cin.ignore();

            airports.push_back(a);

            std::cout << "Airport added.\n";
        }

        // -------- DELETE --------
        else if (choice == 2) {
            std::string code;

            std::cout << "Enter IATA to delete: ";
            std::getline(std::cin, code);

            for (int i = 0; i < airports.size(); i++) {
                if (airports[i].iata == code) {
                    airports.erase(airports.begin() + i);
                    std::cout << "Deleted.\n";
                    break;
                }
            }
        }

        // -------- SAVE --------
        else if (choice == 3) {
            saveCSV("../../data/airports.csv", airports);
        }

        // -------- EXIT --------
        else if (choice == 4) {
            break;
        }
    }
}