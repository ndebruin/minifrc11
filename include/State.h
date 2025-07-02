#pragma once

#include <Arduino.h>

// what state is the robot in?
enum RobotState 
{
    ESTOP = -1,
    Disabled = 0,
    Teleop = 2,
    Auto = 3
};

// basic configuration
enum FieldSide 
{
    Blue = 0,
    Red = 1
};

// what gamepiece are we holding rn?
enum GamePiece 
{
    None = 0,
    CoralGround = 1,
    CoralEE = 2
};

enum ScoreSide
{
    Forward = 0,
    Backward = 1
};
 
// the numbers fundamentally don't matter bc we will just use the names
// this will also include any in-between states that are needed for smooth movement
enum MechState 
{
    // stow states
    StowedEmpty = 0,
    StowedCoralGround = 1,
    StowedCoralEE =2,
    
    Stopped = 99,

    // coral scoring states
    L1EETraveling = 10,
    L1EEReady = 11,
    L1EEScoring = 12,

    L1GroundTraveling = 15,
    L1GroundReady = 16,
    L1GroundScoring = 17,

    L2Traveling = 20,
    L2Ready = 21,
    L2Scoring = 22,

    L3Traveling = 30,
    L3Ready = 31,
    L3Scoring = 32,

    L4Traveling = 40,
    L4Ready = 41,
    L4Scoring = 42, 

    // intake states
    GroundIntakeDeployed = 50,
    GroundIntakeEjecting = 51,
    StationIntakeDeployed = 52,

    // de-algae states
    DeAlgaeL2Ready = 60,
    DeAlgaeL2Scoring = 61,

    DeAlgaeL3Ready = 70,
    DeAlgaeL3Scoring = 71,
    
    // climbing states    
    ClimbDeployed = 90,
    ClimbRetracted = 91

};

// robot or field oriented
enum DrivetrainOrientation 
{
    RobotOriented = 0,
    FieldOriented = 1
};

// autons!
enum Auton 
{
    // dawg IDK what's gonna go in here yet
    Brick = 0
};


class StateStorage
{
    public:
        bool isEnabled(){return robotState > 0;};

        RobotState getRobotState(){return robotState;};
        FieldSide getFieldSide(){return fieldSide;};
        MechState getMechState(){return mechState;};
        DrivetrainOrientation getOrientation(){return drivetrainMoment;};
        Auton getAuto(){return auton;};
        ScoreSide getScoringSide(){return scoreSide;};

        void setRobotState(RobotState state){ robotState = state; };
        void setFieldSide(FieldSide side){ fieldSide = side; };
        void setMechstate(MechState state){ mechState = state; };
        void setAuto(Auton autoMode){ auton = autoMode; };
        void setOrientation(DrivetrainOrientation orientation){ drivetrainMoment = orientation; };
        void setScoreSide(ScoreSide Scoreside){ scoreSide = Scoreside; };


    private:
        RobotState robotState;
        FieldSide fieldSide;
        MechState mechState;
        DrivetrainOrientation drivetrainMoment;
        Auton auton;
        ScoreSide scoreSide;
};
