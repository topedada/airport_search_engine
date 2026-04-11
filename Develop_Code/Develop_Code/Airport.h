#pragma once
#include <string>

struct Airport {
    std::string ident;        
    std::string type;
    std::string name;
    int elevation;
    std::string continent;    
    std::string country;
    std::string iso_region;   
    std::string municipality;
    std::string icao_code;
    std::string iata;
    std::string gps_code;
    std::string local_code;
    double latitude;
    double longitude;
};