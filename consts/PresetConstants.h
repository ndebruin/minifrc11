#pragma once

#include <Arduino.h>

/* 
    this will define whether L2-L4 scoring actions 
    are performed full-auto
    
    to require driver confirmation, set to && (AND)
    to enable full-auto, set to || (OR)
*/
#define FULL_AUTO &&


// This files contains all tuning parameters for preset positions

////////////////////////////////////////////////////////////////////// Timing //////////////////////////////////////////////////////////////////////

// all in ms

// drivetrain areas
constexpr long stationClearTimeout = 1000;
constexpr long reefClearTimeout = 1000;
constexpr long autoAlignTimeout = 1000;

// elevator
constexpr long elevatorClearIntakeTime = 1000;
constexpr long elevatorClearEETime = 1000;
constexpr long elevatorDownTime = 1000; // all small movements (L1 - L3, handoff, clearing intake)
constexpr long elevatorL4Time = 1000; // also used for down
constexpr long elevatorDealgaeL3Time = 1000;

// arm
constexpr long armLowDownTime = 1000; // L1, L2
constexpr long armHighDownTime = 1000; // L3, L4, station intake
constexpr long armStationIntakeTime = 1000;
constexpr long armL1Time = 1000;
constexpr long armL2Time = 1000;
constexpr long armL3Time = 1000;
constexpr long armL4Time = 1000;
constexpr long armScoreTimeout = 1000;

// intake
constexpr long intakeDeployTime = 1000;
constexpr long intakeRetractTime = 1000;
constexpr long intakeHandoffTime = 1000;
constexpr long handoffTimeout = 1000;
constexpr long intakeL1Time = 1000;
constexpr long intakeScoreTimeout = 1000;

// dealgae arm
constexpr long deAlgaeDeployTime = 1000;
constexpr long deAlgaeRetractTime = 1000;
constexpr long deAlgaeTimeout = 1000;

// climber



////////////////////////////////////////////////////////////////////// Intake //////////////////////////////////////////////////////////////////////

constexpr float intakeStowAngle = 90.0;
constexpr float intakeDeployAngle = 90.0;
constexpr float intakeHandoffAngle = 90.0;

constexpr float intakeL1ReadyAngle = 90.0;
constexpr float intakeL1ScoreAngle = 90.0;

//////////////////////////////////////////// EE/Intake Roller //////////////////////////////////////////////////////////////////////

constexpr float intakeRollerIntakeSpeed = -1.0;
constexpr float intakeRollerL1ScoreSpeed = 1.0;

constexpr float eeRollerIntakeSpeed = 1.0;
constexpr float eeRollerL1ScoreSpeed = -1.0;

constexpr float rollerEEHandoffSpeed = 1.0; // ground -> EE
constexpr float rollerGroundHandoffSpeed = -1.0; // EE -> ground

////////////////////////////////////////////////////////////////////// Elevator //////////////////////////////////////////////////////////////////////

constexpr uint16_t elevatorBottomPosition = 1500;
constexpr uint16_t elevatorClearIntakePosition = 1500;
constexpr uint16_t elevatorClearEEPosition = 1500;

constexpr uint16_t elevatorHandoffHighPosition = 1500; // clear everything pos
constexpr uint16_t elevatorHandoffLowPosition = 1500; // actual handoff pos.

constexpr uint16_t elevatorL4Position = 1500;

constexpr uint16_t elevatorDeAlgaeL3Position = 1500;

////////////////////////////////////////////////////////////////////// Arm //////////////////////////////////////////////////////////////////////

// these are gonna be kinda weird bc of the belt up-duction

constexpr float armMiddleAngle = 90.0;

constexpr float armClimbAngle = 90.0;

constexpr float armL1Angle = 90.0;

constexpr float armL2ReadyAngle = 90.0;
constexpr float armL2ScoreAngle = 90.0;

constexpr float armL3ReadyAngle = 90.0;
constexpr float armL3ScoreAngle = 90.0;

constexpr float armL4ReadyAngle = 90.0;
constexpr float armL4ScoreAngle = 90.0;

constexpr float armStationIntakeAngle = 90.0;

////////////////////////////////////////////////////////////////////// Climber //////////////////////////////////////////////////////////////////////

constexpr uint16_t climberStowAngle = 1500;

constexpr uint16_t climberDeployAngle = 1500;

constexpr uint16_t climberClimbAngle = 1500;

////////////////////////////////////////////////////////////////////// De-Algae Arm //////////////////////////////////////////////////////////////////////

constexpr float algaeStartingConfigAngle = 90.0; // only used for legality (& maybe climb)
constexpr float algaeStowAngle = 90.0;
constexpr float algaeInitialDeployAngle = 90.0;
constexpr float algaeFinalDeployAngle = 90.0;

constexpr uint8_t deAlgaefyAttempts = 2;