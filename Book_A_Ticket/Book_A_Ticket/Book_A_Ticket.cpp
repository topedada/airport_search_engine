#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

// ---------------- Structs ----------------
struct Airport {
    std::string name;
    std::string country;
    std::string iata;
};

struct Booking {
    std::string passengerName;
    std::string fromIATA;
    std::string toIATA;
};

// ---------------- Data ----------------
std::vector<Airport> airports;
std::vector<Booking> bookings;

// ---------------- Helpers ----------------
std::string toLower(const std::string& s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return result;
}

// ---------------- Load CSV ----------------
bool loadAirports(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << "\n";
        return false;
    }

    std::string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        Airport a;

        getline(ss, token, ','); // ident, ignore
        getline(ss, token, ','); // type, ignore
        getline(ss, a.name, ',');

        getline(ss, token, ','); // elevation, ignore
        getline(ss, a.country, ',');
        getline(ss, token, ','); // region, ignore
        getline(ss, token, ','); // municipality, ignore
        getline(ss, a.iata, ',');

        if (!a.iata.empty()) {  // only include airports with IATA
            airports.push_back(a);
        }
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
    return true;
}

// ---------------- Print Bookings ----------------
void viewBookings() {
    if (bookings.empty()) {
        std::cout << "No bookings yet.\n";
        return;
    }

    for (size_t i = 0; i < bookings.size(); ++i) {
        std::cout << "Booking " << i + 1 << "\n";
        std::cout << "Passenger: " << bookings[i].passengerName << "\n";
        std::cout << "From: " << bookings[i].fromIATA << "\n";
        std::cout << "To: " << bookings[i].toIATA << "\n";
        std::cout << "----------------------\n";
    }
}

// ---------------- Book Ticket ----------------
bool iataExists(const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) return true;
    }
    return false;
}

void bookTicket() {
    Booking b;

    std::cout << "Enter your name: ";
    std::getline(std::cin, b.passengerName);

    std::cout << "Enter FROM airport (IATA): ";
    std::getline(std::cin, b.fromIATA);

    if (!iataExists(b.fromIATA)) {
        std::cout << "Invalid FROM IATA code.\n";
        return;
    }

    std::cout << "Enter TO airport (IATA): ";
    std::getline(std::cin, b.toIATA);

    if (!iataExists(b.toIATA)) {
        std::cout << "Invalid TO IATA code.\n";
        return;
    }

    bookings.push_back(b);
    std::cout << "Booking confirmed for " << b.passengerName
        << " from " << b.fromIATA << " to " << b.toIATA << "\n";
}

// ---------------- Main Menu ----------------
int main() {
    // Load airports from CSV (airports.csv must be in same folder as .exe)
    if (!loadAirports("airports.csv")) {
        std::cout << "Press Enter to exit...";
        std::cin.get();
        return 1;
    }

    while (true) {
        std::cout << "\n--- Booking Menu ---\n";
        std::cout << "1. Book a Flight\n";
        std::cout << "2. View Bookings\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            bookTicket();
        }
        else if (choice == 2) {
            viewBookings();
        }
        else if (choice == 3) {
            break;
        }
        else {
            std::cout << "Invalid choice.\n";
        }
    }

    std::cout << "Press Enter to exit...";
    std::cin.get();
    return 0;
}