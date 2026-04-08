#include <iostream>
#include <limits>
#include "Airport.h"          // your common header
#include "Book_A_Ticket.h"    // contains bookTicket() and viewBookings()
#include "LoadCSV.h"          // contains loadCSV() and airports vector

int main() {
    // Load the CSV file using the function in LoadCSV.cpp
    loadCSV("../../data/airports.csv");

    int choice;
    std::string input;

    while (true) {
        std::cout << "\n--- Airport Menu ---\n";
        std::cout << "1. Book Ticket\n";
        std::cout << "2. View Bookings\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 3) break;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

        if (choice == 1) {
            bookTicket();      // Calls the function in Book_A_Ticket.cpp
        }
        else if (choice == 2) {
            viewBookings();    // Calls the function in Book_A_Ticket.cpp
        }
        else {
            std::cout << "Invalid option\n";
        }
    }

    return 0;
}