#pragma once
#include <vector>
#include "Airport.h"

struct Booking {
    std::string passenger;
    std::string fromIATA;
    std::string toIATA;
};

bool iataExists(const std::vector<Airport>& airports, const std::string& code);
void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings);
void viewBookings(const std::vector<Booking>& bookings);