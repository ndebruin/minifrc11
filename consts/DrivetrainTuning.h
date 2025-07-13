#pragma once

#include <Arduino.h>

// this file contains control loop tunings for the drivetrain


constexpr double kV = 0.0; // minimum value to overcome friction 
               // determined experimentally

constexpr double driveExp = 1.0; // control "squaring" value to get more control at the low end

// strafe parameters
constexpr double linX_kS = 0.0;
constexpr double linX_kP = 0.0;
constexpr double linX_kI = 0.0;
constexpr double linX_kD = 0.0;

constexpr double x_AcceptableError = 0.0; // mm

// forward back parameters
constexpr double linY_kS = 0.0;
constexpr double linY_kP = 0.0;
constexpr double linY_kI = 0.0;
constexpr double linY_kD = 0.0;

constexpr double y_AcceptableError = 0.0; // mm

// turn parameters
constexpr double angZ_kS = 0.0;
constexpr double angZ_kP = 0.0;
constexpr double angZ_kI = 0.0;
constexpr double angZ_kD = 0.0;

constexpr double theta_AcceptableError =  0.0; // degrees