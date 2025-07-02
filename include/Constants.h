#pragma once

#define robotName "Team 43"

constexpr uint8_t LED = 2;

////////////////////////////////////////////////////////////////////// Drivetrain //////////////////////////////////////////////////////////////////////

constexpr uint8_t frontLeftMotorChannel = 3;
constexpr uint8_t frontRightMotorChannel = 5;
constexpr uint8_t backLeftMotorChannel = 2;
constexpr uint8_t backRightMotorChannel = 1;

constexpr double kV = 0.0; // minimum value to overcome friction 
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
constexpr uint8_t scl = 21;
constexpr uint8_t sda = 22;

// all tuning params have been moved to the rp2040 board, as we now comm over i2c


////////////////////////////////////////////////////////////////////// Intake/EE //////////////////////////////////////////////////////////////////////

constexpr uint8_t intakeServoChannel = 4;
constexpr uint8_t intakeEEMotorChannel = 4;

constexpr uint8_t EESensorPin = 36;
constexpr uint8_t GroundSensorPin = 39;

constexpr float intakeStowAngle = 90.0;
constexpr float intakeDeployAngle = 90.0;
constexpr float intakeHandoffAngle = 90.0;

////////////////////////////////////////////////////////////////////// Elevator //////////////////////////////////////////////////////////////////////

constexpr uint8_t elevatorServoChannel = 2;

constexpr float conversionRatio = 0.0;

////////////////////////////////////////////////////////////////////// Arm //////////////////////////////////////////////////////////////////////

constexpr uint8_t armServoChannel = 1;

////////////////////////////////////////////////////////////////////// Climber //////////////////////////////////////////////////////////////////////

constexpr uint8_t climberServoChannel = 3;

////////////////////////////////////////////////////////////////////// De-Algae Arm //////////////////////////////////////////////////////////////////////

constexpr uint8_t algaeArmServoChannel = 5;

constexpr float algaeStartAngle = 90.0;
constexpr float algaeStowAngle = 90.0;
constexpr float algaeInitialDeployAngle = 90.0;
constexpr float algaeFinalDeployAngle = 90.0;