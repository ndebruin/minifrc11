#pragma once

#define robotName "Team 43"

#define LED 2

////////////////////////////////////////////////////////////////////// Drivetrain //////////////////////////////////////////////////////////////////////

#define frontLeftMotorChannel 3
#define frontRightMotorChannel 5
#define backLeftMotorChannel 2
#define backRightMotorChannel 1

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

#define scl 21
#define sda 22


////////////////////////////////////////////////////////////////////// Intake/EE //////////////////////////////////////////////////////////////////////

#define intakeServoChannel 4
#define intakeEEMotorChannel 4

#define EESensorPin 36
#define GroundSensorPin 39

constexpr float intakeStowAngle = 90.0;
constexpr float intakeDeployAngle = 90.0;
constexpr float intakeHandoffAngle = 90.0;

////////////////////////////////////////////////////////////////////// Elevator //////////////////////////////////////////////////////////////////////

#define elevatorServoChannel 2

constexpr float conversionRatio = 0.0;

////////////////////////////////////////////////////////////////////// Arm //////////////////////////////////////////////////////////////////////

#define armServoChannel

////////////////////////////////////////////////////////////////////// Climber //////////////////////////////////////////////////////////////////////

#define climberServoChannel 3

////////////////////////////////////////////////////////////////////// De-Algae Arm //////////////////////////////////////////////////////////////////////

#define algaeArmServoChannel 5

constexpr float algaeStartAngle = 90.0;
constexpr float algaeStowAngle = 90.0;
constexpr float algaeInitialDeployAngle = 90.0;
constexpr float algaeFinalDeployAngle = 90.0;