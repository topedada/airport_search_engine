#include <iostream>
#include <vector>
#include "LoadCSV.h"
#include "Book_A_Ticket.h"
#include "Admin.h"

int main() {

    std::vector<Airport> airports;
    std::vector<Booking> bookings;

    loadCSV("../../data/airports.csv", airports);

    int choice;
    std::string input;

    while (true) {

        std::cout << "\n====== MAIN MENU ======\n";
        std::cout << "1. Search by Country\n";
        std::cout << "2. Search by Name\n";
        std::cout << "3. Search by IATA\n";
        std::cout << "4. Book Ticket\n";
        std::cout << "5. View Bookings\n";
        std::cout << "6. Admin\n";
        std::cout << "7. Save Bookings\n";
        std::cout << "8. Exit\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input\n";
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (choice == 1) {
            std::cout << "Enter country: ";
            std::getline(std::cin, input);
            searchByCountry(airports, input);
        }

        else if (choice == 2) {
            std::cout << "Enter name: ";
            std::getline(std::cin, input);
            searchByName(airports, input);
        }

        else if (choice == 3) {
            std::cout << "Enter IATA: ";
            std::getline(std::cin, input);
            searchByIATA(airports, input);
        }

        else if (choice == 4) {
            bookTicket(airports, bookings);
        }

        else if (choice == 5) {
            viewBookings(bookings);
        }

        else if (choice == 6) {
            adminAirportMenu(airports);
        }

        else if (choice == 7) {
            saveBookingsToCSV(bookings, "../../data/FlightRecords.csv");
        }

        else if (choice == 8) {
            break;
        }
    }

    return 0;
}