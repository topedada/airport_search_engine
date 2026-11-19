#include "Admin.h"
#include <iostream>
#include <fstream>
#include <vector>

//  INPUT VALIDATION FUNCTIONS 

// Function to safely get an integer from the user
// Keeps asking until a valid number is entered
int getIntInput(const std::string& prompt) {

    int value;

    while (true) {
        std::cout << prompt; // Show message to user

        // If user enters a valid integer
        if (std::cin >> value) {
            std::cin.ignore(10000, '\n'); // Clear leftover input
            return value; // Return the valid number
        }

        // If input is invalid (e.g. letters instead of numbers)
        std::cout << "Invalid input. Must be a number.\n";
        std::cin.clear();                // Reset error state
        std::cin.ignore(10000, '\n');    // Remove bad input
    }
}

// Function to safely get a decimal (double) value
// Prevents program crashing from invalid input
double getDoubleInput(const std::string& prompt) {

    double value;

    while (true) {
        std::cout << prompt; // Show message

        // If valid decimal number entered
        if (std::cin >> value) {
            std::cin.ignore(10000, '\n'); // Clear input buffer
            return value;
        }

        // If invalid input entered
        std::cout << "Invalid input. Must be a number.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}


//  HELPER FUNCTIONS 

// Converts a string to lowercase
// Used to compare text without worrying about capital letters
std::string toLower(std::string s) {
    for (char& c : s) c = tolower(c); // Change each letter to lowercase
    return s;
}


//  FILE HANDLING 

// Saves all airport data into a CSV file
// Each airport is written as one line in the file
void saveCSV(const std::string& filename, const std::vector<Airport>& airports) {

    std::ofstream file(filename); // Open file for writing

    // Check if file opened correctly
    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    // Write column headings (CSV header)
    file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao,iata,gps,local,coordinates\n";

    // Loop through all airports and write their data
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
        // Coordinates are wrapped in quotes to keep them together
    }

    std::cout << "CSV saved successfully\n";
}


//  REMOVE FUNCTION 

// Removes an airport using its IATA code (e.g. LHR)
// Rewrites the CSV file after removing it
void removeAirportByIATA(const std::string& filename, std::vector<Airport>& airports) {

    std::string code;
    std::cout << "Enter IATA code to remove: ";
    std::getline(std::cin, code);

    std::vector<Airport> updated; // New list after removal
    bool found = false;           // Tracks if airport was found

    // Go through all airports
    for (const auto& a : airports) {

        // Keep airport if it DOES NOT match the code
        if (toLower(a.iata) != toLower(code)) {
            updated.push_back(a);
        }
        else {
            found = true; // Airport matched → will be removed
        }
    }

    // If no airport matched the code
    if (!found) {
        std::cout << "Airport not found\n";
        return;
    }

    airports = updated; // Replace old list with updated list

    // Rewrite the CSV file with updated data
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    // Write header again
    file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao,iata,gps,local,coordinates\n";

    // Write all remaining airports
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

    std::cout << "Airport removed successfully\n";
}


//  ADMIN MENU 

// Displays admin options and allows user to:
// 1. Add airport
// 2. Save data
// 3. Remove airport
// 4. Exit menu
void adminAirportMenu(std::vector<Airport>& airports) {

    while (true) {

        // Show menu options
        std::cout << "\n====== ADMIN MENU ======\n";
        std::cout << "1. Add Airport\n";
        std::cout << "2. Save CSV\n";
        std::cout << "3. Remove Airport\n";
        std::cout << "4. Back\n";
        std::cout << "Choice: ";

        int choice;

        // Check for invalid menu input
        if (!(std::cin >> choice)) {
            std::cin.clear();              // Reset error
            std::cin.ignore(10000, '\n');  // Remove bad input
            continue;
        }

        std::cin.ignore(10000, '\n'); // Clear buffer

        //  OPTION 1: ADD AIRPORT 
        if (choice == 1) {

            Airport a; // Create new airport object

            // Get all airport details from user
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

            airports.push_back(a); // Add airport to list

            std::cout << "Airport added successfully\n";
        }

        //  OPTION 2: SAVE 
        else if (choice == 2) {
            saveCSV("../../data/airports.csv", airports);
        }

        //  OPTION 3: REMOVE 
        else if (choice == 3) {
            removeAirportByIATA("../../data/airports.csv", airports);
        }

        //  OPTION 4: EXIT 
        else if (choice == 4) {
            break; // Exit admin menu
        }
    }
}