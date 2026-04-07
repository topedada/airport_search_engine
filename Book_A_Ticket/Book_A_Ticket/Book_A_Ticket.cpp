#include <iostream>
#include <vector>
#include <string>
#include <limits>

// ---------------- Booking Struct ----------------
struct Booking {
    std::string name;
    std::string fromIATA;
    std::string toIATA;
};

// ---------------- Data ----------------
std::vector<Booking> bookings;

// ---------------- Helpers ----------------
std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = tolower(c);  // FIXED
    return result;
}

// ---------------- Book Ticket ----------------
void bookTicket(const std::vector<std::string>& validIATA) {
    Booking b;

    std::cout << "Enter your name: ";
    std::getline(std::cin, b.name);

    // Validate FROM airport
    while (true) {
        std::cout << "Enter departure airport (IATA): ";
        std::getline(std::cin, b.fromIATA);

        bool found = false;
        for (const auto& code : validIATA)
            if (toLower(code) == toLower(b.fromIATA)) { found = true; break; }

        if (found) break;
        std::cout << "Invalid IATA code. Try again.\n";
    }

    // Validate TO airport
    while (true) {
        std::cout << "Enter destination airport (IATA): ";
        std::getline(std::cin, b.toIATA);

        bool found = false;
        for (const auto& code : validIATA)
            if (toLower(code) == toLower(b.toIATA)) { found = true; break; }

        if (found) break;
        std::cout << "Invalid IATA code. Try again.\n";
    }

    bookings.push_back(b);
    std::cout << "Booking successful for " << b.name
        << " from " << b.fromIATA << " to " << b.toIATA << "!\n";
}

// ---------------- View Bookings ----------------
void viewBookings() {
    if (bookings.empty()) {
        std::cout << "No bookings yet.\n";
        return;
    }

    std::cout << "\n--- Bookings ---\n";
    for (size_t i = 0; i < bookings.size(); i++) {
        std::cout << i + 1 << ". " << bookings[i].name
            << " | From: " << bookings[i].fromIATA
            << " | To: " << bookings[i].toIATA << "\n";
    }
}

// ---------------- Main ----------------
int main() {
    // Example list of valid IATA codes (replace later with your CSV list)
    std::vector<std::string> validIATA = { "LAX", "JFK", "CDG", "NRT", "DXB" };

    int choice;
    while (true) {
        std::cout << "\n--- Booking Menu ---\n";
        std::cout << "1. Book a Flight\n";
        std::cout << "2. View Bookings\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) bookTicket(validIATA);
        else if (choice == 2) viewBookings();
        else if (choice == 3) break;
        else std::cout << "Invalid option\n";
    }

    return 0;
}