#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "LoadCSV.h"
#include "Book_A_Ticket.h"

// ---------------- Admin Menu ----------------
void adminMenu() {
    std::string password;
    while (true) {
        std::cout << "Enter admin password (or 'back' to return): ";
        std::getline(std::cin, password);
        if (password == "back") return;
        if (password == "password01") {
            std::cout << "Access granted.\n[Admin features coming soon]\n";
            return;
        }
        std::cout << "Incorrect password, try again.\n";
    }
}

int main() {
    std::vector<Airport> airports;

    // Load airports
    loadCSV("../../data/airports.csv", airports);

    int choice;
    std::string input;

    while (true) {
        std::cout << "\n--- Airport Menu ---\n";
        std::cout << "1. Search by Country\n2. Search by Name\n3. Search by IATA\n";
        std::cout << "4. Book Ticket\n5. View Bookings\n6. Admin\n7. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 7) break;

        if (choice >= 1 && choice <= 3) {
            std::cout << "Enter search: ";
            std::getline(std::cin, input);
            if (choice == 1) searchByCountry(airports, input);
            else if (choice == 2) searchByName(airports, input);
            else if (choice == 3) searchByIATA(airports, input);
        }
        else if (choice == 4) bookTicket();
        else if (choice == 5) viewBookings();
        else if (choice == 6) adminMenu();
        else std::cout << "Invalid option\n";
    }

    std::cout << "Exiting program.\n";
    return 0;
}