#pragma once
#include <vector>
#include <string>
#include "LoadCSV.h"

// ---------------- Booking Struct ----------------
struct Booking {
    std::string passenger;
    std::string fromIATA;
    std::string toIATA;
    double distance; // NEW
};

// ---------------- Functions ----------------
void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings);
void viewBookings(const std::vector<Booking>& bookings);
void saveBookingsToCSV(const std::vector<Booking>& bookings, const std::string& filename);