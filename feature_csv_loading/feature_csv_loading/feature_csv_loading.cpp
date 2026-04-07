#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

// ---------------- Airport Struct ----------------
struct Airport {
    std::string name;
    std::string country;
    std::string iata;
    std::string type;
    std::string municipality;
    double latitude;
    double longitude;
    int elevation;
};

// ---------------- Helpers ----------------
std::string toLower(const std::string& s) {
    std::string result = s;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

double toDouble(const std::string& s) {
    try { return std::stod(s); }
    catch (...) { return 0.0; }
}

int toInt(const std::string& s) {
    try { return std::stoi(s); }
    catch (...) { return 0; }
}

// ---------------- Load CSV ----------------
void loadCSV(const std::string& filename, std::vector<Airport>& airports) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file.\n";
        return;
    }

    std::string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Airport a;

        getline(ss, token, ','); // ident
        getline(ss, a.type, ',');
        getline(ss, a.name, ',');

        getline(ss, token, ',');
        a.elevation = toInt(token);

        getline(ss, token, ','); // continent
        getline(ss, a.country, ',');

        getline(ss, token, ','); // region
        getline(ss, a.municipality, ',');

        getline(ss, token, ','); // icao
        getline(ss, a.iata, ',');

        getline(ss, token, ','); // gps
        getline(ss, token, ','); // local

        getline(ss, token);
        if (!token.empty() && token.front() == '"') token.erase(0, 1);
        if (!token.empty() && token.back() == '"') token.pop_back();

        std::stringstream coord(token);
        std::string lat, lon;
        getline(coord, lat, ',');
        getline(coord, lon, ',');

        a.latitude = toDouble(lat);
        a.longitude = toDouble(lon);

        airports.push_back(a);
    }

    std::cout << "Loaded " << airports.size() << " airports.\n";
}

// ---------------- Print ----------------
void printAirport(const Airport& a) {
    std::cout << "Name: " << a.name << "\n";
    std::cout << "Country: " << a.country << "\n";
    std::cout << "IATA: " << a.iata << "\n";
    std::cout << "Type: " << a.type << "\n";
    std::cout << "Municipality: " << a.municipality << "\n";
    std::cout << "Lat: " << a.latitude
        << ", Lon: " << a.longitude << "\n";
    std::cout << "Elevation: " << a.elevation << "\n";
    std::cout << "----------------------\n";
}

// ---------------- Search Functions ----------------
void searchByCountry(const std::vector<Airport>& airports, const std::string& countryCode) {
    int count = 0;
    for (const auto& a : airports) {
        if (toLower(a.country) == toLower(countryCode)) {
            printAirport(a);
            count++;
            if (count >= 10) break;
        }
    }
    if (count == 0) std::cout << "No airports found.\n";
}

void searchByName(const std::vector<Airport>& airports, const std::string& name) {
    int count = 0;
    for (const auto& a : airports) {
        if (toLower(a.name).find(toLower(name)) != std::string::npos) {
            printAirport(a);
            count++;
            if (count >= 10) break;
        }
    }
    if (count == 0) std::cout << "No airports found.\n";
}

void searchByIATA(const std::vector<Airport>& airports, const std::string& code) {
    for (const auto& a : airports) {
        if (toLower(a.iata) == toLower(code)) {
            printAirport(a);
            return;
        }
    }
    std::cout << "No airport found.\n";
}

// ---------------- PLACEHOLDERS (SAFE FOR MERGING) ----------------
void bookTicket() {
    std::cout << "[Booking system coming soon]\n";
}

void viewBookings() {
    std::cout << "[View bookings coming soon]\n";
}

// ---------------- Admin Login ----------------
void adminMenu() {
    std::string password;

    while (true) {
        std::cout << "Enter admin password (or type 'back' to return): ";
        std::getline(std::cin, password);

        if (password == "back") return;

        if (password == "password01") {
            std::cout << "Access granted.\n";
            // Placeholder for future admin features
            std::cout << "[Admin features coming soon]\n";
            return;
        }
        else {
            std::cout << "Incorrect password, try again.\n";
        }
    }
}

// ---------------- Main ----------------
int main() {
    std::vector<Airport> airports;
    loadCSV("../../data/airports.csv", airports);

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
        std::cout << "7. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (choice == 7) break;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice >= 1 && choice <= 3) {
            std::cout << "Enter search: ";
            getline(std::cin, input);

            if (choice == 1) searchByCountry(airports, input);
            else if (choice == 2) searchByName(airports, input);
            else if (choice == 3) searchByIATA(airports, input);
        }
        else if (choice == 4) bookTicket();
        else if (choice == 5) viewBookings();
        else if (choice == 6) adminMenu();
        else std::cout << "Invalid option\n";
    }

    return 0;
}