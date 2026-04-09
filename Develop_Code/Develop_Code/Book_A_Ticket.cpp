#include "Book_A_Ticket.h"
#include <iostream>
#include <limits>

// Define the bookings vector
std::vector<Booking> bookings;

// Helper function to lowercase strings
std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = tolower(c);
    return result;
}

// Extern vector of airports (defined in LoadCSV.cpp)
extern std::vector<Airport> airports;

bool iataExists(const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) return true;
    }
    return false;
}

// Booking function
void bookTicket() {
    std::string name, from, to;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear buffer

    std::cout << "Passenger Name: ";
    std::getline(std::cin, name);

    std::cout << "From (IATA): ";
    std::getline(std::cin, from);

    std::cout << "To (IATA): ";
    std::getline(std::cin, to);

    if (!iataExists(from) || !iataExists(to)) {
        std::cout << "Invalid airport code.\n";
        return;
    }

    bookings.push_back({ name, from, to });
    std::cout << "Booking successful!\n";
}

// View bookings
void viewBookings() {
    if (bookings.empty()) {
        std::cout << "No bookings yet.\n";
        return;
    }
    for (const auto& b : bookings) {
        std::cout << b.passenger << ": " << b.fromIATA << " -> " << b.toIATA << "\n";
    }
}