#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// ---------------- Structs ----------------
struct Airport {
    std::string name;
    std::string country;
    std::string iata;
};

struct Booking {
    std::string passenger;
    std::string fromIATA;
    std::string toIATA;
};

// ---------------- Data ----------------
std::vector<Airport> airports;
std::vector<Booking> bookings;

// ---------------- Helpers ----------------
std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = tolower(c);
    return result;
}

bool iataExists(const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) return true;
    }
    return false;
}

// ---------------- Load CSV ----------------
void loadCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open " << filename << "\n";
        return;
    }

    std::string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        // Skip columns 0-8 to reach iata_code (column J / index 9)
        for (int i = 0; i < 9; i++) getline(ss, token, ',');

        getline(ss, a.iata, ','); // Column 9: iata_code

        // Optionally get name and country if you want
        getline(ss, token, ','); // gps_code (skip)
        getline(ss, token, ','); // local_code (skip)
        getline(ss, token);       // coordinates (skip)

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// ---------------- Booking ----------------
void bookTicket() {
    std::string passenger, from, to;

    std::cout << "Enter your name: ";
    std::getline(std::cin, passenger);

    std::cout << "Enter FROM airport IATA code: ";
    std::getline(std::cin, from);

    std::cout << "Enter TO airport IATA code: ";
    std::getline(std::cin, to);

    if (!iataExists(from)) {
        std::cout << "FROM airport code not valid.\n";
        return;
    }
    if (!iataExists(to)) {
        std::cout << "TO airport code not valid.\n";
        return;
    }

    bookings.push_back({ passenger, from, to });
    std::cout << "Booking confirmed for " << passenger
        << " from " << from << " to " << to << "\n";
}

// ---------------- Main ----------------
int main() {
    loadCSV("../../data/airports.csv"); // CSV must be in same folder as exe

    if (airports.empty()) return 1;

    while (true) {
        std::cout << "\n--- Book a Ticket ---\n";
        std::cout << "1. Book Flight\n";
        std::cout << "2. View Bookings\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // flush newline

        if (choice == 1) bookTicket();
        else if (choice == 2) {
            if (bookings.empty()) std::cout << "No bookings yet.\n";
            for (const auto& b : bookings) {
                std::cout << b.passenger << ": " << b.fromIATA
                    << " -> " << b.toIATA << "\n";
            }
        }
        else if (choice == 3) break;
        else std::cout << "Invalid option\n";
    }

    return 0;
}