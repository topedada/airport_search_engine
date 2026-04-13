#include "Analytics.h"
#include <iostream>
#include <cmath>
#include "MathUtils.h"

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
        std::cout << nearest->name << "\n";
        std::cout << "IATA: " << nearest->iata << "\n";
        std::cout << "Distance: " << minDistance << " km\n";
    }
}

void advancedMenu(std::vector<Airport>& airports) {

    int choice;

    while (true) {

        std::cout << "\n===== ADVANCED OPTIONS =====\n";
        std::cout << "1. Find nearest airport\n";
        std::cout << "2. Airports within radius\n";
        std::cout << "3. Highest elevation airport\n";
        std::cout << "4. Lowest elevation airport\n";
        std::cout << "5. Missing IATA codes\n";
        std::cout << "6. Sort airports\n";
        std::cout << "7. Back\n";
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

        case 7:
            return;

        default:
            std::cout << "Feature not implemented yet.\n";
            break;
        }
    }
}