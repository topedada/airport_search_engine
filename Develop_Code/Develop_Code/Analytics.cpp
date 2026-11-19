#include "Analytics.h"
#include <iostream>
#include <cmath>
#include "MathUtils.h"
#include <algorithm>
#include <cmath>

//  DISPLAY FUNCTION 

// Prints all details of a single airport
// Used by other functions to avoid repeating code
void printAirport(const Airport& a) {

    std::cout << "\n-----------------------------\n";
    std::cout << "IDENT: " << a.ident << "\n";          // Unique airport ID
    std::cout << "TYPE: " << a.type << "\n";            // Airport type (small, large, etc.)
    std::cout << "NAME: " << a.name << "\n";            // Airport name
    std::cout << "ELEVATION: " << a.elevation << "\n";  // Height above sea level (feet)
    std::cout << "CONTINENT: " << a.continent << "\n";  // Continent code
    std::cout << "COUNTRY: " << a.iso_country << "\n";  // Country code
    std::cout << "REGION: " << a.iso_region << "\n";    // Region/state
    std::cout << "MUNICIPALITY: " << a.municipality << "\n"; // City/town
    std::cout << "ICAO: " << a.icao << "\n";            // ICAO airport code
    std::cout << "IATA: " << a.iata << "\n";            // IATA airport code
    std::cout << "GPS: " << a.gps << "\n";              // GPS identifier
    std::cout << "LOCAL: " << a.local << "\n";          // Local airport code
    std::cout << "LAT: " << a.latitude << "\n";         // Latitude
    std::cout << "LON: " << a.longitude << "\n";        // Longitude
}


//  MISSING IATA FUNCTION 

// Finds and displays airports that do not have an IATA code
void missingIATACodes(const std::vector<Airport>& airports) {

    int count = 0; // Counts how many airports are missing IATA

    std::cout << "\n===== AIRPORTS WITH MISSING IATA =====\n";

    // Loop through all airports
    for (const auto& a : airports) {

        // If IATA field is empty
        if (a.iata.empty()) {
            printAirport(a); // Show airport details
            count++;         // Increase counter
        }
    }

    // Display result
    if (count == 0) {
        std::cout << "No airports with missing IATA codes.\n";
    }
    else {
        std::cout << "\nTotal missing IATA codes: " << count << "\n";
    }
}


//  ELEVATION STATS 

// Finds the highest and lowest airports by elevation
void elevationStats(const std::vector<Airport>& airports) {

    // Check if list is empty
    if (airports.empty()) {
        std::cout << "No airports loaded.\n";
        return;
    }

    const Airport* highest = nullptr; // Pointer to highest airport
    const Airport* lowest = nullptr;  // Pointer to lowest airport

    // Loop through all airports
    for (const auto& a : airports) {

        // Skip invalid values (infinite or not-a-number)
        if (std::isinf(a.elevation) || std::isnan(a.elevation)) {
            continue;
        }

        // First valid airport becomes starting point
        if (highest == nullptr || lowest == nullptr) {
            highest = &a;
            lowest = &a;
            continue;
        }

        // Check for highest elevation
        if (a.elevation > highest->elevation) {
            highest = &a;
        }

        // Check for lowest elevation
        if (a.elevation < lowest->elevation) {
            lowest = &a;
        }
    }

    std::cout << "\n===== ELEVATION STATS =====\n";

    // If no valid data found
    if (highest == nullptr || lowest == nullptr) {
        std::cout << "No valid elevation data found.\n";
        return;
    }

    // Display highest airport
    std::cout << "\nHighest Airport:\n";
    printAirport(*highest);
    std::cout << "Elevation: " << highest->elevation << " ft\n";

    // Display lowest airport
    std::cout << "\nLowest Airport:\n";
    printAirport(*lowest);
    std::cout << "Elevation: " << lowest->elevation << " ft\n";
}


//  NEAREST AIRPORT 

// Finds the closest airport to a given location
void findNearestAirport(const std::vector<Airport>& airports) {

    double lat, lon;

    // Get user coordinates
    std::cout << "Enter latitude: ";
    std::cin >> lat;

    std::cout << "Enter longitude: ";
    std::cin >> lon;

    const Airport* nearest = nullptr; // Store closest airport
    double minDistance = 1e9;         // Start with a very large distance

    // Convert user input to radians (needed for formula)
    double lat1 = toRad(lat);
    double lon1 = toRad(lon);

    // Loop through all airports
    for (const auto& a : airports) {

        // Convert airport coordinates to radians
        double lat2 = toRad(a.latitude);
        double lon2 = toRad(a.longitude);

        // Difference between coordinates
        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;

        // Haversine formula (calculates distance on Earth)
        double h = sin(dLat / 2) * sin(dLat / 2) +
            cos(lat1) * cos(lat2) *
            sin(dLon / 2) * sin(dLon / 2);

        double c = 2 * atan2(sqrt(h), sqrt(1 - h));

        double distance = 6371 * c; // Earth radius = 6371 km

        // Update nearest airport if this one is closer
        if (distance < minDistance) {
            minDistance = distance;
            nearest = &a;
        }
    }

    // Display result
    if (nearest) {
        std::cout << "\nNearest Airport:\n";
        printAirport(*nearest);
        std::cout << "Distance: " << minDistance << " km\n";
    }
}


//  AIRPORTS WITHIN RADIUS 

// Finds all airports within a given distance from user location
void airportsWithinRadius(const std::vector<Airport>& airports) {

    double lat, lon, radius;

    // Get user input
    std::cout << "Enter latitude: ";
    std::cin >> lat;

    std::cout << "Enter longitude: ";
    std::cin >> lon;

    std::cout << "Enter radius (km): ";
    std::cin >> radius;

    // Convert user coordinates to radians
    double lat1 = toRad(lat);
    double lon1 = toRad(lon);

    bool found = false; // Track if any airport matches

    std::cout << "\nAirports within " << radius << " km:\n";

    // Loop through all airports
    for (const auto& a : airports) {

        // Convert airport coordinates
        double lat2 = toRad(a.latitude);
        double lon2 = toRad(a.longitude);

        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;

        // Haversine formula again
        double h = sin(dLat / 2) * sin(dLat / 2) +
            cos(lat1) * cos(lat2) *
            sin(dLon / 2) * sin(dLon / 2);

        double c = 2 * atan2(sqrt(h), sqrt(1 - h));

        double distance = 6371 * c;

        // If airport is within given radius
        if (distance <= radius) {

            printAirport(a);
            std::cout << "Distance: " << distance << " km\n";

            found = true;
        }
    }

    // If no airports found
    if (!found) {
        std::cout << "No airports found in this radius.\n";
    }
}


//  ADVANCED MENU 

// Menu for accessing all analytics features
void advancedMenu(std::vector<Airport>& airports) {

    int choice;

    while (true) {

        // Display menu options
        std::cout << "\n===== ADVANCED OPTIONS =====\n";
        std::cout << "1. Find nearest airport\n";
        std::cout << "2. Airports within radius\n";
        std::cout << "3. Highest/Lowest elevation airport\n";
        std::cout << "4. Missing IATA codes\n";
        std::cout << "5. Back\n";
        std::cout << "Choice: ";

        // Handle invalid input (e.g. letters instead of numbers)
        if (!(std::cin >> choice)) {
            std::cin.clear();                // Reset error
            std::cin.ignore(10000, '\n');    // Remove invalid input
            continue;
        }

        std::cin.ignore(10000, '\n'); // Clear buffer

        // Run selected option
        switch (choice) {

        case 1:
            findNearestAirport(airports);
            break;

        case 2:
            airportsWithinRadius(airports);
            break;

        case 3:
            elevationStats(airports);
            break;

        case 4:
            missingIATACodes(airports);
            break;

        case 5:
            return; // Exit menu

        default:
            std::cout << "Feature not implemented yet.\n";
            break;
        }
    }
}