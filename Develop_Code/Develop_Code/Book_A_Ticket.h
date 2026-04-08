#pragma once
#include <string>
#include <vector>
#include "Airport.h"

// Booking struct
struct Booking {
    std::string passenger;
    std::string fromIATA;
    std::string toIATA;
};

// Declare the global vector for bookings
extern std::vector<Booking> bookings;

// Function declarations
void bookTicket();
void viewBookings();