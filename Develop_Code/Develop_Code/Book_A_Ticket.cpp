#include "Book_A_Ticket.h"
#include "LoadCSV.h"
#include <iostream>
#include <fstream>
#include <cmath>

// -------- Distance --------
double toRadians(double degree) {
    return degree * 3.141592653589793 / 180.0;
}

double calculateDistance(const Airport& a, const Airport& b) {
    double lat1 = toRadians(a.latitude);
    double lon1 = toRadians(a.longitude);
    double lat2 = toRadians(b.latitude);
    double lon2 = toRadians(b.longitude);

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double h = sin(dLat / 2) * sin(dLat / 2) +
        cos(lat1) * cos(lat2) *
        sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(h), sqrt(1 - h));

    return 6371 * c; // KM
}

// -------- Helper --------
bool iataExists(const std::vector<Airport>& airports, const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) return true;
    }
    return false;
}

// -------- Book Ticket --------
void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings) {
    std::string passenger, from, to;

    std::cout << "Enter your name: ";
    std::getline(std::cin, passenger);

    std::cout << "Enter FROM airport IATA code: ";
    std::getline(std::cin, from);

    std::cout << "Enter TO airport IATA code: ";
    std::getline(std::cin, to);

    if (passenger.empty() || from.empty() || to.empty()) {
        std::cout << "All fields are required.\n";
        return;
    }

    const Airport* fromAirport = nullptr;
    const Airport* toAirport = nullptr;

    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(from)) fromAirport = &a;
        if (toLower(a.iata) == toLower(to)) toAirport = &a;
    }

    if (!fromAirport) {
        std::cout << "FROM airport code not valid.\n";
        return;
    }

    if (!toAirport) {
        std::cout << "TO airport code not valid.\n";
        return;
    }

    double distance = calculateDistance(*fromAirport, *toAirport);

    bookings.push_back({ passenger, from, to, distance });

    std::cout << "Booking confirmed for " << passenger
        << " from " << from << " to " << to << "\n";
    std::cout << "Distance: " << distance << " km\n";
}

// -------- View Bookings --------
void viewBookings(const std::vector<Booking>& bookings) {
    if (bookings.empty()) {
        std::cout << "No bookings yet.\n";
        return;
    }

    for (const auto& b : bookings) {
        std::cout << b.passenger << ": "
            << b.fromIATA << " -> "
            << b.toIATA
            << " | Distance: " << b.distance << " km\n";
    }
}

// -------- Save Bookings --------
void saveBookingsToCSV(const std::vector<Booking>& bookings, const std::string& filename) {

    if (bookings.empty()) {
        std::cout << "No bookings to save.\n";
        return;
    }

    std::ofstream file(filename); 

    if (!file.is_open()) {
        std::cout << "Failed to open " << filename << "\n";
        return;
    }

    // Header
    file << "Passenger,FromIATA,ToIATA,Distance\n";

    for (const auto& b : bookings) {
        file << b.passenger << ","
            << b.fromIATA << ","
            << b.toIATA << ","
            << b.distance << "\n";
    }

    std::cout << "Bookings saved successfully to " << filename << "\n";
}