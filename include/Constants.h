#pragma once

#define robotName "Team 43"

////////////////////////////////////////////////////////////////////// Drivetrain //////////////////////////////////////////////////////////////////////

#define frontLeftMotorChannel 5
#define frontRightMotorChannel 1
#define backLeftMotorChannel 6
#define backRightMotorChannel 2 

constexpr double kS = 0.0; // minimum value to overcome friction 
               // determined experimentally

constexpr double driveExp = 1.5; // control "squaring" value to get more control at the low end

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


////////////////////////////////////////////////////////////////////// Controller //////////////////////////////////////////////////////////////////////

constexpr double deadzoneValue = 0.1;

constexpr uint8_t axisLinY = 1;
constexpr uint8_t axisLinX = 0;
constexpr uint8_t axisAngZ = 2;

////////////////////////////////////////////////////////////////////// Pose Estimator //////////////////////////////////////////////////////////////////////
constexpr double DPI = 600.0; // 250 Dots per inch NEED TO TUNE

constexpr double MOUSE_CONVERSION_FACTOR = (1.0/DPI); 

constexpr uint baudRate = 115200;
