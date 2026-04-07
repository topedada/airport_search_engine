#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

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
std::vector<Airport> airports;
std::vector<Booking> bookings;

// ---------------- Helpers ----------------
std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) c = tolower(c);
    return result;
}

// Check if the IATA exists in loaded airports
bool isValidIATA(const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) return true;
    }
    return false;
}

// ---------------- Load CSV ----------------
void loadCSV(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filepath << "\n";
        return;
    }

    std::string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        getline(ss, token, ',');        // ident (skip)
        getline(ss, a.iata, ',');       // IATA column
        getline(ss, a.name, ',');       // Name column
        getline(ss, a.country, ',');    // Country column

        // Skip empty IATA codes
        if (a.iata.empty()) continue;

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// ---------------- Book Ticket ----------------
void bookTicket() {
    Booking b;
    std::cout << "Enter your name: ";
    std::getline(std::cin, b.name);

    // Validate FROM IATA
    do {
        std::cout << "Enter departure airport (IATA): ";
        std::getline(std::cin, b.fromIATA);
        if (!isValidIATA(b.fromIATA))
            std::cout << "Invalid IATA. Please enter a valid airport code.\n";
    } while (!isValidIATA(b.fromIATA));

    // Validate TO IATA
    do {
        std::cout << "Enter destination airport (IATA): ";
        std::getline(std::cin, b.toIATA);
        if (!isValidIATA(b.toIATA))
            std::cout << "Invalid IATA. Please enter a valid airport code.\n";
    } while (!isValidIATA(b.toIATA));

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
    for (size_t i = 0; i < bookings.size(); i++) {
        std::cout << "Booking " << i + 1 << "\n";
        std::cout << "Name: " << bookings[i].name << "\n";
        std::cout << "From: " << bookings[i].fromIATA << "\n";
        std::cout << "To: " << bookings[i].toIATA << "\n";
        std::cout << "----------------------\n";
    }
}

// ---------------- Main ----------------
int main() {
    // CSV is in parent folder of feature_booking_system
    std::string csvPath = "../airports"; // or "../airports.csv" if your file has .csv extension
    loadCSV(csvPath);

    int choice;
    while (true) {
        std::cout << "\n--- Booking Menu ---\n";
        std::cout << "1. Book a Ticket\n";
        std::cout << "2. View Bookings\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) bookTicket();
        else if (choice == 2) viewBookings();
        else if (choice == 3) break;
        else std::cout << "Invalid choice.\n";
    }

    return 0;
}