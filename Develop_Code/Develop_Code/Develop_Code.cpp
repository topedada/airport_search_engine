#include <iostream>
#include <vector>
#include "LoadCSV.h"
#include "Book_A_Ticket.h"
#include "Admin.h"
#include "Analytics.h"

int main() {

    //creating the vector list 
    std::vector<Airport> airports;   // Stores all airport data from CSV
    std::vector<Booking> bookings;   // Stores all user flight bookings

    // Load airport data from file into the airports vector
    loadCSV("../../data/airports.csv", airports); //loads airport data from a CSV file and stores it into the airports vector as Airport objects

    int choice;        // Stores user's menu choice
    std::string input; // Stores user input (search text, etc.)

    // Main program loop (runs until user exits)
    while (true) {

        //  MAIN MENU 
        std::cout << "\n====== Nottingham SkyRoute Explorer ======\n";
        std::cout << "1. Search by Country\n";
        std::cout << "2. Search by Name\n";
        std::cout << "3. Search by IATA\n";
        std::cout << "4. Book Ticket\n";
        std::cout << "5. View Bookings\n";
        std::cout << "6. Count Airport Types\n";
        std::cout << "7. Advanced Options\n";
        std::cout << "8. Admin\n";
        std::cout << "9. Save Bookings\n";
        std::cout << "10.Exit\n";
        std::cout << "Choice: ";

        //  INPUT VALIDATION 

        // Check if user entered a valid number
        if (!(std::cin >> choice)) {//waits for the user to type something stors it in choice 
            std::cin.clear();                // Reset error flag
            std::cin.ignore(10000, '\n');    // Remove invalid input untill you reach a new line 
            std::cout << "Invalid input\n";
            continue; // Restart loop
        }

        std::cin.ignore(10000, '\n'); // Clear leftover input

        //  MENU OPTIONS 

        switch (choice) {

            //  SEARCH BY COUNTRY 
            //getline = get a whole line of text including spaces”
        case 1:
            std::cout << "Enter country: ";
            std::getline(std::cin, input);//waits for the user to type something and save it into input 
            searchByCountry(airports, input); // Call search function passess the veriable airport and variables string input 
            break;

            //  SEARCH BY NAME 
        case 2:
            std::cout << "Enter name: ";
            std::getline(std::cin, input);
            searchByName(airports, input);
            break;

            //  SEARCH BY IATA CODE 
        case 3:
            std::cout << "Enter IATA: ";
            std::getline(std::cin, input);
            searchByIATA(airports, input);
            break;

            //  BOOK A TICKET 
        case 4://all the work is already written inside the function bookTicket
            bookTicket(airports, bookings); // Adds a booking to the list
            break;

            //  VIEW BOOKINGS 
        case 5:
            viewBookings(bookings); // Displays all saved bookings
            break;

            //  COUNT AIRPORT TYPES 
        case 6:
            countAirportTypes(airports); // Shows number of each airport type
            break;

            //  ADVANCED ANALYTICS 
        case 7:
            advancedMenu(airports); // Opens advanced features menu
            break;

            //  ADMIN MENU 
        case 8: {
            std::string password;

            // Ask for admin password
            std::cout << "Enter admin password: ";
            std::getline(std::cin, password);

            // Check password before allowing access
            if (password == "password01") {
                adminAirportMenu(airports); // Open admin features
            }
            else {
                std::cout << "Incorrect password. Access denied.\n";
            }
            break;
        }

              //  SAVE BOOKINGS TO FILE 
        case 9:
            saveBookingsToCSV(bookings, "../../data/FlightRecords.csv");
            break;

            //  EXIT PROGRAM 
        case 10:
            std::cout << "Exiting program...\n";
            return 0; // Ends the program

            //  INVALID OPTION 
        default:
            std::cout << "Invalid choice\n";
        }
    }
}