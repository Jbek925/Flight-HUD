#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// Function to parse flight data from a string
std::vector<std::string> parseFlightData(const std::string& data);

// Function to format speed from knots to kilometers per hour
double formatSpeedKPH(double speed_knots);

// Function to convert degrees to radians
double degreesToRadians(double degrees);

// Function to convert radians to degrees
double radiansToDegrees(double radians);

#endif // UTILS_H