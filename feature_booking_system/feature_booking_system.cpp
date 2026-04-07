#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

// ---------------- Structs ----------------
struct Airport {
    std::string name;
    std::string country;
    std::string iata;
};

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
    for (char& c : result) c = tolower(c);
    return result;
}

// Check if IATA exists in airports vector
bool isValidIATA(const std::vector<Airport>& airports, const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) return true;
    }
    return false;
}

// ---------------- Book Ticket ----------------
void bookTicket(const std::vector<Airport>& airports) {
    Booking b;
    std::cout << "Enter your name: ";
    std::getline(std::cin, b.name);

    // Validate FROM IATA
    do {
        std::cout << "Enter departure airport (IATA): ";
        std::getline(std::cin, b.fromIATA);
        if (!isValidIATA(airports, b.fromIATA))
            std::cout << "Invalid IATA. Please enter a valid airport code.\n";
    } while (!isValidIATA(airports, b.fromIATA));

    // Validate TO IATA
    do {
        std::cout << "Enter destination airport (IATA): ";
        std::getline(std::cin, b.toIATA);
        if (!isValidIATA(airports, b.toIATA))
            std::cout << "Invalid IATA. Please enter a valid airport code.\n";
    } while (!isValidIATA(airports, b.toIATA));

    bookings.push_back(b);
    std::cout << "Booking successful!\n";
}

// ---------------- View Bookings ----------------
void viewBookings() {
    if (bookings.empty()) {
        std::cout << "No bookings found.\n";
        return;
    }

    std::cout << "\n--- Bookings ---\n";
    for (int i = 0; i < bookings.size(); i++) {
        std::cout << "Booking " << i + 1 << "\n";
        std::cout << "Name: " << bookings[i].name << "\n";
        std::cout << "From: " << bookings[i].fromIATA << "\n";
        std::cout << "To: " << bookings[i].toIATA << "\n";
        std::cout << "----------------------\n";
    }
}

// ---------------- Main ----------------
int main() {
    // Example airport list loaded from CSV
    std::vector<Airport> airports = {
        {"Heathrow", "UK", "LHR"},
        {"John F. Kennedy", "USA", "JFK"},
        {"Charles de Gaulle", "France", "CDG"}
    };

    int choice;
    while (true) {
        std::cout << "\n--- Booking Menu ---\n";
        std::cout << "1. Book a Ticket\n";
        std::cout << "2. View Bookings\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) bookTicket(airports);
        else if (choice == 2) viewBookings();
        else if (choice == 3) break;
        else std::cout << "Invalid choice.\n";
    }

    return 0;
}