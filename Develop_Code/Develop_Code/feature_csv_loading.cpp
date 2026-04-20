#include "LoadCSV.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

// LOWERCASE HELP 

// Converts a string to lowercase so comparisons are case-insensitive
// s is a variable that stores data and gives it to the function 
std::string toLower(const std::string& s) { // paramter defines the data the function revices and works with
// the function will revice the data from input string s it want the orginal data not a copy and it wants it to be a constant
//:tolower is an inbuilt function within c++

    std::string result = s;//stored the data in s into result local variable 

    // Loop through each character and convert it to lowercase
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
// through each character in the variable result .begin is the starting location .end is the end point 3.being is the save desitination. :tolower calls the function

    return result; //returns the lowercase string from the function back to wherever the function was called
}

// Cleans up airport type text (handles _, -, and spaces)
//turn SMALL-AIRPORT", "SMALL_AIRPORT", "SMALL AIRPORT into small airport 
std::string normaliseType(std::string s) {// function returns a string wanta copy of input string s
// changes the data heavily so a copy is ok 

    std::string result;//creates empty string to conatin the clean version 

    // Loop through each character in the string
    for (char c : s) {//loops through strig s one character at a time

        // If character is a separator, replace it with a space
        if (c == '_' || c == '-' || c == ' ') {
            result += ' ';// if the aiport has one of those character replace it with a space 
        }
        else {
            // Otherwise convert character to lowercase and add it
            result += std::tolower(c);
        }
    }

    return result; // Sends the cleaned string back to wherever the function was call
}

// Counts how many airports are large, small, or heliports
//Void since it doesn't return data back to other part of the code. void means function does not send any data back 
void countAirportTypes(const std::vector<Airport>& airports) {// retuns nothing, list of airport object, use the orginal list do not make a copy or modify it
    // count variable 
    int large = 0; 
    int small = 0;
    int heliport = 0;

    // Loop through every airport in the list
    for (const auto& a : airports) {// a means one airport at a time. auto& no copy

        // Clean the type string so it is easier to compare
        std::string type = normaliseType(a.type); //takes a.type like SMALL-AIRPORT cleans it into a standard format like small airport

        //If you remove != std::string::npos, the condition becomes unreliable 
        // because C++ treats the index as a boolean, which can incorrectly fail when the match is at position 0.
        // Check what type the airport is and increase counters
        if (type.find("large") != std::string::npos) {//type.find returns the position of the matching string so if it was fouth it will return 4 
            large++;                                  //returns std::string::npos the value was found in the string 
        }
        else if (type.find("small") != std::string::npos) {
            small++;
        }
        else if (type.find("heliport") != std::string::npos) {
            heliport++;
        }
    }

    // Display final counts to the user
    std::cout << "\n===== AIRPORT TYPE COUNT =====\n";
    std::cout << "Large Airports: " << large << "\n";
    std::cout << "Small Airports: " << small << "\n";
    std::cout << "Heliports: " << heliport << "\n";
}

// LOAD CSV 

// Reads airport data from a CSV file and stores it in a vector
void loadCSV(const std::string& filename, std::vector<Airport>& airports) {
    //Opens a CSV file → reads each airport → converts it into an Airport object → stores it in the airports vector
    //recives the input veriable file, recives the Airport type list adn recives the airports input veriable 
    std::ifstream file(filename); // Open a file for reading, using the filename

    // Check if file opened correctly
    if (!file.is_open()) {// if file fails print error stop function return
        std::cout << "Error opening CSV file\n";
        return;
    }

    std::string line;

    // Skip the first line (header row in CSV)
    std::getline(file, line);

    // Read file line by line (each airport record)
    while (std::getline(file, line)) {

        std::stringstream ss(line); // Used to split CSV line into parts
        Airport a; // Create a new airport object

        //csv Reads thing has text so we have to save it has text
        std::string elevationStr; // Stores elevation as text first
        std::string coordinates;   // Stores lat/lon together

        // Read each column from the CSV line (in order)
        // a is one airport object that holds all its related fields togethe
        std::getline(ss, a.ident, ',');
        std::getline(ss, a.type, ',');
        std::getline(ss, a.name, ',');
        std::getline(ss, elevationStr, ',');
        std::getline(ss, a.continent, ',');
        std::getline(ss, a.iso_country, ',');
        std::getline(ss, a.iso_region, ',');
        std::getline(ss, a.municipality, ',');
        std::getline(ss, a.icao, ',');
        std::getline(ss, a.iata, ',');
        std::getline(ss, a.gps, ',');
        std::getline(ss, a.local, ',');
        std::getline(ss, coordinates);

        // Convert elevation from string to number
        try {
            a.elevation = std::stod(elevationStr);
        }
        catch (...) {
            // If conversion fails, set to 0
            a.elevation = 0;
        }

        // Remove quotes ("") from coordinates string (if any exist)
        coordinates.erase(
            std::remove(coordinates.begin(), coordinates.end(), '\"'),
            coordinates.end()
        );

        // Find comma between latitude and longitude
        size_t pos = coordinates.find(',');

        // If comma exists, split into lat and lon
        if (pos != std::string::npos) {
            try {
                a.latitude = std::stod(coordinates.substr(0, pos));//gets everthing before the commer and converts it to a number saves it into a.latitude
                a.longitude = std::stod(coordinates.substr(pos + 1));// gets everthing after the commer and converts it to a number saves it into a.longitude
            }// std:stod = string to double
            catch (...) {
                // If conversion fails, set default values
                a.latitude = 0;
                a.longitude = 0;
            }
        }
        else {
            // If format is wrong, set default values
            a.latitude = 0;
            a.longitude = 0;
        }

        // Add airport to the list
        airports.push_back(a);//It adds the fully filled Airport object a into the airports vector 
    }

    // Show how many airports were loaded
    std::cout << "Loaded " << airports.size() << " airports\n";
}

//  SEARCH BY NAME 

// Search for airports using part of the name (not case sensitive)
void searchByName(const std::vector<Airport>& airports, const std::string& input) {
    //Searches through all airports and prints any airport whose name matches the user’s input.
    // const std::vector<Airport>& airports The full list of airports(read - only), const std::string& input What the user typed to search for
    bool found = false; // Tracks if we found anything

    // Loop through all airports
    for (const auto& a : airports) {// loops through each airport one airport at a time 
    //auto tells C++ You figure out the type automatically
        // Check if airport name contains search text
        if (toLower(a.name).find(toLower(input)) != std::string::npos) {// convert both string to lowercase 
            //check if the match exist 
            std::cout << "\n--- AIRPORT FOUND ---\n";

            // Display full airport details
            std::cout << "Name: " << a.name << "\n";
            std::cout << "Ident: " << a.ident << "\n";
            std::cout << "Type: " << a.type << "\n";
            std::cout << "Elevation: " << a.elevation << "\n";
            std::cout << "Continent: " << a.continent << "\n";
            std::cout << "Country: " << a.iso_country << "\n";
            std::cout << "Region: " << a.iso_region << "\n";
            std::cout << "Municipality: " << a.municipality << "\n";
            std::cout << "ICAO: " << a.icao << "\n";
            std::cout << "IATA: " << a.iata << "\n";
            std::cout << "GPS: " << a.gps << "\n";
            std::cout << "Local: " << a.local << "\n";
            std::cout << "Latitude: " << a.latitude << "\n";
            std::cout << "Longitude: " << a.longitude << "\n";

            found = true; // Mark that we found a match
            //needed to print the nwe found message without it the user would get no feedback at a
        }
    }

    // If nothing was found, tell the user
    if (!found) {
        std::cout << "No airport found\n";
    }
}

// SEARCH BY IATA 

// Search for airport using exact IATA code
void searchByIATA(const std::vector<Airport>& airports, const std::string& input) {

    bool found = false;

    for (const auto& a : airports) {

        // Compare IATA codes (case insensitive)
        if (toLower(a.iata) == toLower(input)) {

            std::cout << "\n--- AIRPORT FOUND ---\n";

            // Show key airport details
            std::cout << "Name: " << a.name << "\n";
            std::cout << "Ident: " << a.ident << "\n";
            std::cout << "Type: " << a.type << "\n";
            std::cout << "Elevation: " << a.elevation << "\n";
            std::cout << "Country: " << a.iso_country << "\n";
            std::cout << "Region: " << a.iso_region << "\n";
            std::cout << "ICAO: " << a.icao << "\n";
            std::cout << "IATA: " << a.iata << "\n";
            std::cout << "Latitude: " << a.latitude << "\n";
            std::cout << "Longitude: " << a.longitude << "\n";

            found = true;
        }
    }

    if (!found) {
        std::cout << "No airport found\n";
    }
}

//  SEARCH BY COUNTRY 

// Search for airports by country code
void searchByCountry(const std::vector<Airport>& airports, const std::string& input) {

    bool found = false;

    for (const auto& a : airports) {

        // Compare country codes (case insensitive)
        if (toLower(a.iso_country) == toLower(input)) {

            std::cout << "\n--- AIRPORT FOUND ---\n";

            // Display airport information
            std::cout << "Name: " << a.name << "\n";
            std::cout << "Ident: " << a.ident << "\n";
            std::cout << "Type: " << a.type << "\n";
            std::cout << "Elevation: " << a.elevation << "\n";
            std::cout << "Country: " << a.iso_country << "\n";
            std::cout << "Region: " << a.iso_region << "\n";
            std::cout << "ICAO: " << a.icao << "\n";
            std::cout << "IATA: " << a.iata << "\n";
            std::cout << "Latitude: " << a.latitude << "\n";
            std::cout << "Longitude: " << a.longitude << "\n";

            found = true;
        }
    }

    // If no results found
    if (!found) {
        std::cout << "No airports found in this country\n";
    }
}