#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "LoadCSV.h"
#include "Book_A_Ticket.h"
#include "Admin.h"

int main() {
    std::vector<Airport> airports;
    std::vector<Booking> bookings;

    loadCSV("../../data/airports.csv", airports);

    if (airports.empty()) {
        std::cout << "No airports loaded.\n";
        return 1;
    }

    int choice;
    std::string input;

    while (true) {
        std::cout << "\n--- MENU ---\n";
        std::cout << "1. Search by Country\n";
        std::cout << "2. Search by Name\n";
        std::cout << "3. Search by IATA\n";
        std::cout << "4. Book Ticket\n";
        std::cout << "5. View Bookings\n";
        std::cout << "6. Admin Menu\n";
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
            else searchByIATA(airports, input);
        }

        else if (choice == 4) {
            bookTicket(airports, bookings);
        }

        else if (choice == 5) {
            viewBookings(bookings);
        }

        else if (choice == 6) {
            std::string password;
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);

            if (password == "password01") {
                adminAirportMenu(airports);
            }
        }
        else if (choice == 7) {
            saveBookingsToCSV(bookings, "../../data/FlightRecords.csv");

            std::cout << "All bookings saved \n";
        }

        else {
            std::cout << "Invalid option\n";
        }
    }

    return 0;
}