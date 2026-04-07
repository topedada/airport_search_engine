#include <iostream>
#include <vector>
#include <string>
#include <limits>

// ---------------- Struct ----------------
struct Booking {
    std::string name;
    std::string fromIATA;
    std::string toIATA;
};

// ---------------- Data ----------------
std::vector<Booking> bookings;

// ---------------- Book Ticket ----------------
void bookTicket() {
    Booking b;

    std::cout << "Enter your name: ";
    std::getline(std::cin, b.name);

    std::cout << "Enter departure airport (IATA): ";
    std::getline(std::cin, b.fromIATA);

    std::cout << "Enter destination airport (IATA): ";
    std::getline(std::cin, b.toIATA);

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
    int choice;

    while (true) {
        std::cout << "\n--- Booking Menu ---\n";
        std::cout << "1. Book a Ticket\n";
        std::cout << "2. View Bookings\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear newline

        if (choice == 1) bookTicket();
        else if (choice == 2) viewBookings();
        else if (choice == 3) break;
        else std::cout << "Invalid choice.\n";
    }

    return 0;
}