#pragma once
#include <vector>
#include <string>
#include "LoadCSV.h"  // so we can use Airport struct

// ---------------- Booking Struct ----------------
struct Booking {
    std::string passenger;
    std::string fromIATA;
    std::string toIATA;
};

// ---------------- Functions ----------------
void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings);
void viewBookings(const std::vector<Booking>& bookings);