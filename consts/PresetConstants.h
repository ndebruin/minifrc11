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
constexpr long stationClearTimeout = 3000;
constexpr long reefClearTimeout = 3000;
constexpr long autoAlignTimeout = 2000;

// elevator
constexpr long elevatorClearIntakeTime = 450;
constexpr long elevatorClearEETime = 300;
constexpr long elevatorDownTime = 500; // all small movements (L1 - L3, handoff, clearing intake)
constexpr long elevatorL4Time = 950; // also used for down
constexpr long elevatorDealgaeL3Time = 500;

// arm
constexpr long armLowDownTime = 250; // L1, L2
constexpr long armHighDownTime = 500; // L3, L4, station intake
constexpr long armStationIntakeTime = 500;
constexpr long armL1Time = 250;
constexpr long armL2Time = 250;
constexpr long armL3Time = 500;
constexpr long armL4Time = 500;

constexpr long armScoreTimeout = 1500;

// intake
constexpr long intakeDeployTime = 400;
constexpr long intakeRetractTime = 400;
constexpr long intakeHandoffTime = 100;
constexpr long intakeL1Time = 300;

constexpr long handoffTimeout = 1000;
constexpr long intakeScoreTimeout = 2000;

// dealgae arm
constexpr long deAlgaeDeployTime = 100;
constexpr long deAlgaeRetractTime = 100;

constexpr long deAlgaeTimeout = 3000;

// climber



////////////////////////////////////////////////////////////////////// Intake //////////////////////////////////////////////////////////////////////

constexpr float intakeStowAngle = 6.0;
constexpr float intakeDeployAngle = 184.0;
constexpr float intakeHandoffAngle = 35.0;

constexpr float intakeL1ReadyAngle = 90.0;
constexpr float intakeL1ScoreAngle = 97.0;

//////////////////////////////////////////// EE/Intake Roller //////////////////////////////////////////////////////////////////////

constexpr float intakeRollerIntakeSpeed = -1.0;
constexpr float intakeRollerL1ScoreSpeed = 1.0;

constexpr float eeRollerIntakeSpeed = 1.0;
constexpr float eeRollerL1ScoreSpeed = -1.0;

constexpr float rollerEEHandoffSpeed = 1.0; // ground -> EE
constexpr float rollerGroundHandoffSpeed = -1.0; // EE -> ground

////////////////////////////////////////////////////////////////////// Elevator //////////////////////////////////////////////////////////////////////

constexpr uint16_t elevatorBottomPosition = 750;
constexpr uint16_t elevatorClearIntakePosition = 1200;
constexpr uint16_t elevatorClearEEPosition = 1000;

constexpr uint16_t elevatorHandoffHighPosition = 1200; // clear everything pos
constexpr uint16_t elevatorHandoffLowPosition = 950; // actual handoff pos.

constexpr uint16_t elevatorL4Position = 2000;

constexpr uint16_t elevatorDeAlgaeL3Position = 1500;

////////////////////////////////////////////////////////////////////// Arm //////////////////////////////////////////////////////////////////////

// these are gonna be kinda weird bc of the belt up-duction

constexpr float armMiddleAngle = 101.0;

constexpr float armClimbAngle = 90.0;

constexpr float armL1FowardAngle = 70.0;
constexpr float armL1BackwardAngle = 132.0;

constexpr float armL2ForwardReadyAngle = 52.5;
constexpr float armL2ForwardScoreAngle = 75.0;
constexpr float armL2BackwardReadyAngle = 148.0;
constexpr float armL2BackwardScoreAngle = 125.0;

constexpr float armL3ForwardReadyAngle = 32.0;
constexpr float armL3ForwardScoreAngle = 50.0;
constexpr float armL3BackwardReadyAngle = 167.0;
constexpr float armL3BackwardScoreAngle = 150.0;

constexpr float armL4ForwardReadyAngle = 32.0;
constexpr float armL4ForwardScoreAngle = 50.0;
constexpr float armL4BackwardReadyAngle = 167.0;
constexpr float armL4BackwardScoreAngle = 150.0;

constexpr float armForwardStationIntakeAngle = 90.0;
constexpr float armBackwardStationIntakeAngle = 155.0;

////////////////////////////////////////////////////////////////////// Climber //////////////////////////////////////////////////////////////////////

constexpr uint16_t climberStowAngle = 500;

constexpr uint16_t climberDeployAngle = 1200;

constexpr uint16_t climberClimbAngle = 2200;

////////////////////////////////////////////////////////////////////// De-Algae Arm //////////////////////////////////////////////////////////////////////

constexpr float algaeStartingConfigAngle = 18.0; // only used for legality (& maybe climb)
constexpr float algaeStowAngle = 175.0;
constexpr float algaeInitialDeployAngle = 75.0;
constexpr float algaeFinalDeployAngle = 135.0;

constexpr uint8_t deAlgaefyAttempts = 2;