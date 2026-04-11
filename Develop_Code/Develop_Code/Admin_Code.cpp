#include "Admin.h"
#include "LoadCSV.h"   //  REQUIRED for generateIdent
#include <iostream>
#include <fstream>
#include <limits>

// ---------------- SAFE NUMBER INPUT ----------------
double getDoubleInput(const std::string& prompt) {
    double value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Numbers only.\n";
        }
        else {
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}

int getIntInput(const std::string& prompt) {
    int value;

    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Numbers only.\n";
        }
        else {
            std::cin.ignore(10000, '\n');
            return value;
        }
    }
}

// ---------------- SAVE CSV ----------------
void saveCSV(const std::string& filename, const std::vector<Airport>& airports) {

    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file.\n";
        return;
    }

    file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao_code,iata_code,gps_code,local_code,coordinates\n";

    for (const auto& a : airports) {

        file << a.ident << ","              //  FIXED (NO MORE 0)
            << a.type << ","
            << a.name << ","
            << a.elevation << ","
            << "NA" << ","
            << a.country << ","
            << "NA" << ","
            << a.municipality << ","
            << "NA" << ","
            << a.iata << ","
            << "NA" << ","
            << "NA" << ","
            << a.latitude << ";" << a.longitude << "\n";
    }

    std::cout << "Saved successfully.\n";
}

// ---------------- ADMIN MENU ----------------
void adminAirportMenu(std::vector<Airport>& airports) {

    while (true) {
        std::cout << "\n--- ADMIN MENU ---\n";
        std::cout << "1. Add Airport\n";
        std::cout << "2. Delete Airport\n";
        std::cout << "3. Save\n";
        std::cout << "4. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        // FIX LOOP BUG
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        // -------- ADD AIRPORT --------
        if (choice == 1) {
            Airport a;

            // 🔥 AUTO-GENERATE IDENT (FIX)
            a.ident = std::to_string(generateIdent(airports));

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

            // SAFE NUMERIC INPUT
            a.latitude = getDoubleInput("Latitude: ");
            a.longitude = getDoubleInput("Longitude: ");
            a.elevation = getIntInput("Elevation: ");

            airports.push_back(a);

            std::cout << "Airport added with ID: " << a.ident << "\n";
        }

        // -------- DELETE AIRPORT --------
        else if (choice == 2) {
            std::string code;

            std::cout << "Enter IATA code to delete: ";
            std::getline(std::cin, code);

            bool found = false;

            for (int i = 0; i < airports.size(); i++) {
                if (airports[i].iata == code) {
                    airports.erase(airports.begin() + i);
                    std::cout << "Deleted.\n";
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Airport not found.\n";
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

        else {
            std::cout << "Invalid option.\n";
        }
    }
}