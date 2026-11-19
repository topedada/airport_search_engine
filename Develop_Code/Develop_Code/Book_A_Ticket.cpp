#include "Book_A_Ticket.h"
#include "LoadCSV.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "MathUtils.h"

//  DISTANCE CALCULATION 

// Calculates the distance between two airports using their coordinates
// Uses the Haversine formula to get distance on the Earth's surface
double calculateDistance(const Airport& a, const Airport& b) {

    // Convert latitude and longitude from degrees to radians
    double lat1 = toRad(a.latitude);
    double lon1 = toRad(a.longitude);
    double lat2 = toRad(b.latitude);
    double lon2 = toRad(b.longitude);

    // Calculate differences between coordinates
    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    // Haversine formula (used to calculate distance between two points on Earth)
    double h = sin(dLat / 2) * sin(dLat / 2) +
        cos(lat1) * cos(lat2) *
        sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(h), sqrt(1 - h));

    return 6371 * c; // Return distance in kilometres (Earth radius = 6371 km)
}


//  BOOK TICKET 

// Allows the user to book a flight between two airports
void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings) {

    std::string name, from, to;

    // Get passenger name
    std::cout << "Passenger name: ";
    std::getline(std::cin, name);

    // Get departure and destination airport codes
    std::cout << "From IATA: ";
    std::getline(std::cin, from);

    std::cout << "To IATA: ";
    std::getline(std::cin, to);

    const Airport* a = nullptr; // Departure airport
    const Airport* b = nullptr; // Destination airport

    // Search for airports that match the given IATA codes
    for (const auto& x : airports) {

        // Match departure airport
        if (toLower(x.iata) == toLower(from))
            a = &x;

        // Match destination airport
        if (toLower(x.iata) == toLower(to))
            b = &x;
    }

    // If either airport is not found
    if (!a || !b) {
        std::cout << "Invalid airports\n";
        return;
    }

    // Calculate distance between selected airports
    double dist = calculateDistance(*a, *b);

    // Create and store booking
    bookings.push_back({ name, from, to, dist });

    // Confirm booking to user
    std::cout << "Booking confirmed\nDistance: " << dist << " km\n";
}


//  VIEW BOOKINGS 

// Displays all booked flights
void viewBookings(const std::vector<Booking>& bookings) {

    // If no bookings exist
    if (bookings.empty()) {
        std::cout << "No flights booked yet\n";
        return;
    }

    // Loop through all bookings and display them
    for (const auto& b : bookings) {
        std::cout << b.passenger << " "
            << b.fromIATA << " -> "
            << b.toIATA << " "
            << b.distance << " km\n";
    }
}


//  SAVE BOOKINGS 

// Saves all bookings into a CSV file
// Uses append mode so previous data is not overwritten
void saveBookingsToCSV(const std::vector<Booking>& bookings, const std::string& filename) {

    // Open file in append mode (adds new data instead of replacing)
    std::ofstream file(filename, std::ios::app);

    // Check if file opened correctly
    if (!file.is_open()) {
        std::cout << "Error opening file\n";
        return;
    }

    // Move pointer to end of file to check if it's empty
    file.seekp(0, std::ios::end);

    // If file is empty, write column headers first
    if (file.tellp() == 0) {
        file << "Passenger,FromIATA,ToIATA,Distance\n";
    }

    // Write each booking as a new row in the CSV file
    for (const auto& b : bookings) {
        file << b.passenger << ","
            << b.fromIATA << ","
            << b.toIATA << ","
            << b.distance << "\n";
    }

    std::cout << "Bookings saved (appended)\n";
}