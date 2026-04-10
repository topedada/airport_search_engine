#include "Book_A_Ticket.h"
#include "LoadCSV.h"
#include <iostream>
#include <fstream>

// ---------------- Booking Functions ----------------
bool iataExists(const std::vector<Airport>& airports, const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) return true;
    }
    return false;
}

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

    if (!iataExists(airports, from)) {
        std::cout << "FROM airport code not valid.\n";
        return;
    }

    if (!iataExists(airports, to)) {
        std::cout << "TO airport code not valid.\n";
        return;
    }

    bookings.push_back({ passenger, from, to });

    std::cout << "Booking confirmed for " << passenger
        << " from " << from << " to " << to << "\n";
}

void viewBookings(const std::vector<Booking>& bookings) {
    if (bookings.empty()) {
        std::cout << "No bookings yet.\n";
        return;
    }

    for (const auto& b : bookings) {
        std::cout << b.passenger << ": "
            << b.fromIATA << " -> "
            << b.toIATA << "\n";
    }
}

// ---------------- Save Bookings ----------------
void saveBookingsToCSV(const std::vector<Booking>& bookings, const std::string& filename) {
    std::ofstream file(filename, std::ios::app); // append mode

    if (!file.is_open()) {
        std::cout << "Failed to open " << filename << "\n";
        return;
    }

    // Write header only if file is empty
    file.seekp(0, std::ios::end);
    if (file.tellp() == 0) {
        file << "Passenger,FromIATA,ToIATA\n";
    }

    for (const auto& b : bookings) {
        file << b.passenger << ","
            << b.fromIATA << ","
            << b.toIATA << "\n";
    }

    std::cout << "Bookings saved to " << filename << "\n";
}