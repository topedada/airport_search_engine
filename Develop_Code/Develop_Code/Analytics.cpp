#include "Analytics.h"
#include <iostream>
#include <cmath>
#include "MathUtils.h"
#include <algorithm>

void printAirport(const Airport& a) {

    std::cout << "\n-----------------------------\n";
    std::cout << "IDENT: " << a.ident << "\n";
    std::cout << "TYPE: " << a.type << "\n";
    std::cout << "NAME: " << a.name << "\n";
    std::cout << "ELEVATION: " << a.elevation << "\n";
    std::cout << "CONTINENT: " << a.continent << "\n";
    std::cout << "COUNTRY: " << a.iso_country << "\n";
    std::cout << "REGION: " << a.iso_region << "\n";
    std::cout << "MUNICIPALITY: " << a.municipality << "\n";
    std::cout << "ICAO: " << a.icao << "\n";
    std::cout << "IATA: " << a.iata << "\n";
    std::cout << "GPS: " << a.gps << "\n";
    std::cout << "LOCAL: " << a.local << "\n";
    std::cout << "LAT: " << a.latitude << "\n";
    std::cout << "LON: " << a.longitude << "\n";
}

void missingIATACodes(const std::vector<Airport>& airports) {

    int count = 0;

    std::cout << "\n===== AIRPORTS WITH MISSING IATA =====\n";

    for (const auto& a : airports) {

        if (a.iata.empty()) {
            printAirport(a);
            count++;
        }
    }

    if (count == 0) {
        std::cout << "No airports with missing IATA codes.\n";
    }
    else {
        std::cout << "\nTotal missing IATA codes: " << count << "\n";
    }
}

void elevationStats(const std::vector<Airport>& airports) {

    if (airports.empty()) {
        std::cout << "No airports loaded.\n";
        return;
    }

    const Airport* highest = &airports[0];
    const Airport* lowest = &airports[0];

    for (const auto& a : airports) {

        if (a.elevation > highest->elevation) {
            highest = &a;
        }

        if (a.elevation < lowest->elevation) {
            lowest = &a;
        }
    }

    std::cout << "\n===== ELEVATION STATS =====\n";

    std::cout << "\nHighest Airport:\n";
    printAirport(*highest);
    std::cout << "Elevation: " << highest->elevation << " ft\n";

    std::cout << "\nLowest Airport:\n";
    printAirport(*lowest);
    std::cout << "Elevation: " << lowest->elevation << " ft\n";
}

void findNearestAirport(const std::vector<Airport>& airports) {

    double lat, lon;

    std::cout << "Enter latitude: ";
    std::cin >> lat;

    std::cout << "Enter longitude: ";
    std::cin >> lon;

    const Airport* nearest = nullptr;
    double minDistance = 1e9;

    double lat1 = toRad(lat);
    double lon1 = toRad(lon);

    for (const auto& a : airports) {

        double lat2 = toRad(a.latitude);
        double lon2 = toRad(a.longitude);

        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;

        double h = sin(dLat / 2) * sin(dLat / 2) +
            cos(lat1) * cos(lat2) *
            sin(dLon / 2) * sin(dLon / 2);

        double c = 2 * atan2(sqrt(h), sqrt(1 - h));

        double distance = 6371 * c;

        if (distance < minDistance) {
            minDistance = distance;
            nearest = &a;
        }
    }

    if (nearest) {
        std::cout << "\nNearest Airport:\n";
        printAirport(*nearest);
        std::cout << "Distance: " << minDistance << " km\n";
    }
}

void airportsWithinRadius(const std::vector<Airport>& airports) {

    double lat, lon, radius;

    std::cout << "Enter latitude: ";
    std::cin >> lat;

    std::cout << "Enter longitude: ";
    std::cin >> lon;

    std::cout << "Enter radius (km): ";
    std::cin >> radius;

    double lat1 = toRad(lat);
    double lon1 = toRad(lon);

    bool found = false;

    std::cout << "\nAirports within " << radius << " km:\n";

    for (const auto& a : airports) {

        double lat2 = toRad(a.latitude);
        double lon2 = toRad(a.longitude);

        double dLat = lat2 - lat1;
        double dLon = lon2 - lon1;

        double h = sin(dLat / 2) * sin(dLat / 2) +
            cos(lat1) * cos(lat2) *
            sin(dLon / 2) * sin(dLon / 2);

        double c = 2 * atan2(sqrt(h), sqrt(1 - h));

        double distance = 6371 * c;

        if (distance <= radius) {

            printAirport(a);
            std::cout << "Distance: " << distance << " km\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "No airports found in this radius.\n";
    }
}

void advancedMenu(std::vector<Airport>& airports) {

    int choice;

    while (true) {

        std::cout << "\n===== ADVANCED OPTIONS =====\n";
        std::cout << "1. Find nearest airport\n";
        std::cout << "2. Airports within radius\n";
        std::cout << "3. Highest/Lowest elevation airport\n";
        std::cout << "4. Missing IATA codes\n";
        std::cout << "5. Back\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::cin.ignore(10000, '\n');

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
            return;

        default:
            std::cout << "Feature not implemented yet.\n";
            break;
        }
    }
}