#pragma once  // Ensures this file is only included once
//Function Declerations tells c++ that this functions exist and how it should be used 

#include <vector>       // For using vectors (lists)
#include "LoadCSV.h"   // Includes Airport structure and CSV functions

// Shows advanced options menu
void advancedMenu(std::vector<Airport>& airports);
//creates list of type Airport and airport is the actual list of veriables 

// Finds the nearest airport based on user input location
void findNearestAirport(const std::vector<Airport>& airports);

// Finds all airports within a certain distance (radius)
void airportsWithinRadius(const std::vector<Airport>& airports);

// Shows highest and lowest elevation airports
void elevationStats(const std::vector<Airport>& airports);

// Displays airports that have no IATA code
void missingIATACodes(const std::vector<Airport>& airports);

// Prints all details of a single airport
void printAirport(const Airport& a);
//works the same has the other functions but prints a single aiport while the other will print a list of airports 