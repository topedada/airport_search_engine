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

        switch (choice) {

        case 1:
            std::cout << "Enter country: ";
            std::getline(std::cin, input);
            searchByCountry(airports, input);
            break;

        case 2:
            std::cout << "Enter name: ";
            std::getline(std::cin, input);
            searchByName(airports, input);
            break;

        case 3:
            std::cout << "Enter IATA: ";
            std::getline(std::cin, input);
            searchByIATA(airports, input);
            break;

        case 4:
            bookTicket(airports, bookings);
            break;

        case 5:
            viewBookings(bookings);
            break;

        case 6: {
            std::string password;
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);

            if (password == "password01") {
                adminAirportMenu(airports);
            }
            else {
                std::cout << "Incorrect password. Access denied.\n";
            }
            break;
        }

        case 7:
            saveBookingsToCSV(bookings, "../../data/FlightRecords.csv");
            break;

        case 8:
            std::cout << "Exiting program...\n";
            return 0;

        default:
            std::cout << "Invalid choice\n";
        }
    }
}