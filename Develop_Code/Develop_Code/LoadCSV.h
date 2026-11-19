#pragma once  // Ensures this file is only included once

#include <vector>   // For using vectors (lists)
#include <string>   // For using strings
#include "Airport.h" // Includes Airport structure


// Loads airport data from a CSV file into the vector
void loadCSV(const std::string& filename, std::vector<Airport>& airports);

// Counts how many airports there are by type (e.g. small, large)
void countAirportTypes(const std::vector<Airport>& airports);
// in actual code it will loop through all airport check the type and count how many of each type exit 

// Converts a string to lowercase (for easier searching)
std::string toLower(const std::string& s);
// std::string returns a string. const std::string& s input string . s name of the input veriable. what ever it function is will be returned has lower 

// Search functions for finding airports

// Searches airports by name
void searchByName(const std::vector<Airport>& airports, const std::string& input);
//function will recive the list of Airports and allow users to input a string 
// Searches airports by IATA code
void searchByIATA(const std::vector<Airport>& airports, const std::string& input);
//function will recive the list of Airports and allow users to input a string 
// Searches airports by country
void searchByCountry(const std::vector<Airport>& airports, const std::string& input);
//function will recive the list of Airports and allow users to input a string 