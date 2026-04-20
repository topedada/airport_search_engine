#pragma once  // Makes sure this file is only included once

#include <cmath> // Allows use of math functions

// Function to convert degrees to radians
inline double toRad(double d) {
    return d * 3.141592653589793 / 180.0; // Formula: degrees × (pi / 180)
}