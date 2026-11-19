#pragma once  // Ensures this file is only included once

//Function declarations tells c++ that this functions exist and how it should be used 

#include <vector>   // For using vectors (lists)
#include <string>   // For using strings
#include "Airport.h" // Includes Airport structure

// Shows admin menu for managing airports
void adminAirportMenu(std::vector<Airport>& airports);//function will use a vector list of Airport Object and it will use the orgianl list not make a copy 
//std::vector<Airport> defines the strcuture/type of the list and aiport is the actul list of object in memory that stors the airport data
 
// Saves airport data to a CSV file
void saveCSV(const std::string& filename, const std::vector<Airport>& airports);
//function that will save a list of Airport objects into a CSV file

// Gets a valid integer input from the user
int getIntInput(const std::string& prompt);
//It displays a message and returns the user’s integer input.

// Gets a valid decimal (double) input from the user
double getDoubleInput(const std::string& prompt);
//Show a message to the user, take a decimal number input, and return it. 