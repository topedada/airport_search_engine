#include "Book_A_Ticket.h"
#include "LoadCSV.h"
#include <iostream>
#include <fstream>
#include <cmath>

double toRad(double d) {
    return d * 3.141592653589793 / 180.0;
}

double calculateDistance(const Airport& a, const Airport& b) {

    double lat1 = toRad(a.latitude);
    double lon1 = toRad(a.longitude);
    double lat2 = toRad(b.latitude);
    double lon2 = toRad(b.longitude);

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double h = sin(dLat / 2) * sin(dLat / 2) +
        cos(lat1) * cos(lat2) *
        sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(h), sqrt(1 - h));

    return 6371 * c;
}

void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings) {

    std::string name, from, to;

    std::cout << "Passenger name: ";
    std::getline(std::cin, name);

    std::cout << "From IATA: ";
    std::getline(std::cin, from);

    std::cout << "To IATA: ";
    std::getline(std::cin, to);

    const Airport* a = nullptr;
    const Airport* b = nullptr;

    for (const auto& x : airports) {
        if (toLower(x.iata) == toLower(from)) a = &x;
        if (toLower(x.iata) == toLower(to)) b = &x;
    }

    if (!a || !b) {
        std::cout << "Invalid airports\n";
        return;
    }

    double dist = calculateDistance(*a, *b);

    bookings.push_back({ name, from, to, dist });

    std::cout << "Booking confirmed\nDistance: " << dist << " km\n";
}

void viewBookings(const std::vector<Booking>& bookings) {

    if (bookings.empty()) {
        std::cout << "No flights booked yet\n";
        return;
    }

    for (const auto& b : bookings) {
        std::cout << b.passenger << " "
            << b.fromIATA << " -> "
            << b.toIATA << " "
            << b.distance << " km\n";
    }
}

void saveBookingsToCSV(const std::vector<Booking>& bookings, const std::string& filename) {

    std::ofstream file(filename, std::ios::app);

    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    // Check if file is empty before writing header
    file.seekp(0, std::ios::end);
    if (file.tellp() == 0) {
        file << "Passenger,FromIATA,ToIATA,Distance\n";
    }

    for (const auto& b : bookings) {
        file << b.passenger << ","
            << b.fromIATA << ","
            << b.toIATA << ","
            << b.distance << "\n";
    }

    std::cout << "Bookings saved (appended)\n";
}