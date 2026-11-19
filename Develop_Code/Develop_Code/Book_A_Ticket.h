#pragma once  // Ensures this file is only included once

#include <vector>   // For using vectors (lists)
#include <string>   // For using strings
#include "Airport.h" // Includes Airport structure

// Structure to store booking details
struct Booking {
    std::string passenger; // Passenger name
    std::string fromIATA;  // Departure airport (IATA code)
    std::string toIATA;    // Destination airport (IATA code)
    double distance;       // Distance between airports
};

// Function to book a ticket
void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings);
// describes the function of the code to create two list one of Airport and one for booking 

// Function to display all bookings
void viewBookings(const std::vector<Booking>& bookings);

// Saves bookings to a CSV file
void saveBookingsToCSV(const std::vector<Booking>& bookings, const std::string& filename);
//take data from booking vector and save it into the csv 

// Calculates distance between two airports
double calculateDistance(const Airport& a, const Airport& b);
//takr the distance of the first airpot and the distance of the second airport 