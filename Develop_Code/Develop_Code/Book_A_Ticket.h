#pragma once
#include <vector>
#include <string>
#include "Airport.h"

struct Booking {
    std::string passenger;
    std::string fromIATA;
    std::string toIATA;
    double distance;
};

void bookTicket(const std::vector<Airport>& airports, std::vector<Booking>& bookings);
void viewBookings(const std::vector<Booking>& bookings);
void saveBookingsToCSV(const std::vector<Booking>& bookings, const std::string& filename);
double calculateDistance(const Airport& a, const Airport& b);