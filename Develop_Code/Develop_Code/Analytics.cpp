#include "Analytics.h"
#include <iostream>

void advancedMenu(std::vector<Airport>& airports) {

    int choice;

    while (true) {

        std::cout << "\n===== ADVANCED OPTIONS =====\n";
        std::cout << "1. Find nearest airport\n";
        std::cout << "2. Airports within radius\n";
        std::cout << "3. Highest elevation airport\n";
        std::cout << "4. Lowest elevation airport\n";
        std::cout << "5. Missing IATA codes\n";
        std::cout << "6. Sort airports\n";
        std::cout << "7. Back\n";
        std::cout << "Choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        std::cin.ignore(10000, '\n');

        if (choice == 7) return;

    }
}