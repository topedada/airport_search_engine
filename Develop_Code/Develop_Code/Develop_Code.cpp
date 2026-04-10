#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "LoadCSV.h"
#include "Book_A_Ticket.h"

int main() {
    std::vector<Airport> airports;
    std::vector<Booking> bookings;

    // ---------------- Load CSV ----------------
    loadCSV("../../data/airports.csv", airports);

    if (airports.empty()) {
        std::cout << "No airports loaded. Exiting program.\n";
        system("pause");
        return 1;
    }

    int choice;
    std::string input;

    while (true) {
        std::cout << "\n--- Airport Menu ---\n";
        std::cout << "1. Search by Country\n";
        std::cout << "2. Search by Name\n";
        std::cout << "3. Search by IATA\n";
        std::cout << "4. Book Ticket\n";
        std::cout << "5. View Bookings\n";
        std::cout << "6. Admin\n";
        std::cout << "7. Save Bookings to CSV\n";
        std::cout << "8. Exit\n";
        std::cout << "Choice: ";

        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 8) break;

        if (choice >= 1 && choice <= 3) {
            std::cout << "Enter search: ";
            std::getline(std::cin, input);

            if (choice == 1) searchByCountry(airports, input);
            else if (choice == 2) searchByName(airports, input);
            else if (choice == 3) searchByIATA(airports, input);
        }
        else if (choice == 4) {
            bookTicket(airports, bookings);
        }
        else if (choice == 5) {
            viewBookings(bookings);
        }
        else if (choice == 6) {
            std::string password;
            while (true) {
                std::cout << "Enter admin password (or type 'back' to return): ";
                std::getline(std::cin, password);

                if (password == "back") break;

                if (password == "password01") {
                    std::cout << "Access granted. [Admin features coming soon]\n";
                    break;
                }
                else {
                    std::cout << "Incorrect password, try again.\n";
                }
            }
        }
        else if (choice == 7) {
            saveBookingsToCSV(bookings, "../../data/FlightRecords.csv");

            // Optional: prevent duplicate saves
            bookings.clear();
        }
        else {
            std::cout << "Invalid option\n";
        }
    }

    std::cout << "Goodbye!\n";
    return 0;
}