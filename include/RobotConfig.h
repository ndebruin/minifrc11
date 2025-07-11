#pragma once

#define robotName "Team 43"

constexpr uint8_t LED = 2;

// This file contains all values that are crucial for configuring the physical bits of the robot, like the motor/servo channels, and joystick mappings

////////////////////////////////////////////////////////////////////// Drivetrain //////////////////////////////////////////////////////////////////////

constexpr uint8_t frontLeftMotorChannel = 3;
constexpr uint8_t frontRightMotorChannel = 5;
constexpr uint8_t backLeftMotorChannel = 2;
constexpr uint8_t backRightMotorChannel = 1;

////////////////////////////////////////////////////////////////////// Controller //////////////////////////////////////////////////////////////////////

constexpr double deadzoneValue = 0.1;

constexpr uint8_t axisLinY = 1;
constexpr uint8_t axisLinX = 0;
constexpr uint8_t axisAngZ = 2;

// ABXY
constexpr uint8_t buttonL4 = 0;
constexpr uint8_t buttonL3 = 1;
constexpr uint8_t buttonL2 = 2;
constexpr uint8_t buttonL1 = 3;

// shoulder buttons
constexpr uint8_t buttonDeAlgae = 5;
constexpr uint8_t buttonGroundIntake = 6;

// triggers
constexpr uint8_t buttonExecLeft = 7;
constexpr uint8_t buttonExecRight = 8;

// dpad somewhere
constexpr uint8_t buttonStationIntake = 10;
constexpr uint8_t buttonTriggerClimb = 6; // i still dk how climb is gonna work

////////////////////////////////////////////////////////////////////// Pose Estimator //////////////////////////////////////////////////////////////////////
constexpr uint8_t scl = 21;
constexpr uint8_t sda = 22;

// all tuning params have been moved to the rp2040 board, as we now comm over i2c

////////////////////////////////////////////////////////////////////// Intake/EE //////////////////////////////////////////////////////////////////////

constexpr uint8_t intakeServoChannel = 4;
constexpr uint8_t intakeEEMotorChannel = 4;

constexpr uint8_t EESensorPin = 36;
constexpr uint8_t GroundSensorPin = 39;

constexpr uint16_t EESensorThreshold = 3200;
constexpr bool EESensorReverse = true;
constexpr uint16_t GroundSensorThreshold = 2200;

////////////////////////////////////////////////////////////////////// Elevator //////////////////////////////////////////////////////////////////////

constexpr uint8_t elevatorServoChannel = 2;

constexpr float elevatorConversionRatio = 0.0;

////////////////////////////////////////////////////////////////////// Arm //////////////////////////////////////////////////////////////////////

constexpr uint8_t armServoChannel = 1;

constexpr float armConversionRatio = 0.0;

////////////////////////////////////////////////////////////////////// Climber //////////////////////////////////////////////////////////////////////

constexpr uint8_t climberServoChannel = 3;

////////////////////////////////////////////////////////////////////// De-Algae Arm //////////////////////////////////////////////////////////////////////

constexpr uint8_t algaeArmServoChannel = 5;

