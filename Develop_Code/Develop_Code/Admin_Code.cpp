#include "Admin.h"
#include <iostream>
#include <fstream>

// ================= INPUT VALIDATION =================

int getIntInput(const std::string& prompt) {

    int value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            std::cin.ignore(10000, '\n');
            return value;
        }

        std::cout << "Invalid input. Must be a number.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

double getDoubleInput(const std::string& prompt) {

    double value;

    while (true) {
        std::cout << prompt;

        if (std::cin >> value) {
            std::cin.ignore(10000, '\n');
            return value;
        }

        std::cout << "Invalid input. Must be a number.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

// ================= SAVE CSV =================

void saveCSV(const std::string& filename, const std::vector<Airport>& airports) {

    std::ifstream checkFile(filename);
    bool isEmpty = checkFile.peek() == std::ifstream::traits_type::eof();
    checkFile.close();

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    // write header ONLY if file is empty
    if (isEmpty) {
        file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao,iata,gps,local,coordinates\n";
    }

    for (const auto& a : airports) {
        file << a.ident << ","
            << a.type << ","
            << a.name << ","
            << a.elevation << ","
            << a.continent << ","
            << a.iso_country << ","
            << a.iso_region << ","
            << a.municipality << ","
            << a.icao << ","
            << a.iata << ","
            << a.gps << ","
            << a.local << ","
            << "\"" << a.latitude << "," << a.longitude << "\"\n";
    }

    std::cout << "CSV appended successfully\n";
}

// ================= ADMIN MENU =================

void adminAirportMenu(std::vector<Airport>& airports) {

    while (true) {

        std::cout << "\n====== ADMIN MENU ======\n";
        std::cout << "1. Add Airport\n";
        std::cout << "2. Save CSV\n";
        std::cout << "3. Back\n";
        std::cout << "Choice: ";

        int choice;

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (choice == 1) {

            Airport a;

            std::cout << "IDENT: "; getline(std::cin, a.ident);
            std::cout << "TYPE: "; getline(std::cin, a.type);
            std::cout << "NAME: "; getline(std::cin, a.name);

            a.elevation = getDoubleInput("Elevation: ");

            std::cout << "CONTINENT: "; getline(std::cin, a.continent);
            std::cout << "COUNTRY: "; getline(std::cin, a.iso_country);
            std::cout << "REGION: "; getline(std::cin, a.iso_region);
            std::cout << "MUNICIPALITY: "; getline(std::cin, a.municipality);
            std::cout << "ICAO: "; getline(std::cin, a.icao);
            std::cout << "IATA: "; getline(std::cin, a.iata);
            std::cout << "GPS: "; getline(std::cin, a.gps);
            std::cout << "LOCAL: "; getline(std::cin, a.local);

            a.latitude = getDoubleInput("Latitude: ");
            a.longitude = getDoubleInput("Longitude: ");

            airports.push_back(a);

            std::cout << "Airport added successfully\n";
        }

        else if (choice == 2) {
            saveCSV("../../data/airports.csv", airports);
        }

        else if (choice == 3) {
            break;
        }
    }
}