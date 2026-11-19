#pragma once  // Ensures this file is only included once

#include <string> // For using strings
//structure of the Airport list 
// 
// Structure to store airport data
struct Airport {
    std::string ident;        // Unique airport ID
    std::string type;         // Type of airport (small, large, etc.)
    std::string name;         // Airport name
    double elevation;         // Elevation in feet
    std::string continent;    // Continent code (e.g. EU, NA)
    std::string iso_country;  // Country code (e.g. GB, US)
    std::string iso_region;   // Region code
    std::string municipality; // City or town
    std::string icao;         // ICAO code
    std::string iata;         // IATA code
    std::string gps;          // GPS code
    std::string local;        // Local airport code
    double latitude;          // Latitude coordinate
    double longitude;         // Longitude coordinate
};