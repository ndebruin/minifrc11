#pragma once

#include <Arduino.h>

// what state is the robot in?
enum RobotState {
    Disabled = 0,
    Teleop = 1,
    Auto = 2,
    ESTOP = 3
};

// basic configuration
enum FieldSide {
    Blue = 0,
    Red = 1
};

// what gamepiece are we holding rn?
enum GamePiece {
    None = 0,
    Coral = 1,
    Algae = 2
};

// the numbers fundamentally don't matter bc we will just use the names
// this will also include any in-between states that are needed for smooth movement
enum MechState {
    Stowed = 0,
    Stopped = 1,

    // intake states
    SlowCoralIntake = 10,
    FastCoralIntake = 11,
    ReverseCoralIntake = 12,

    AlgaeIntakeL2 = 13,
    AlgaeIntakeL3 = 14,

    // scoring states
    L1 = 20,
    L2 = 21, 
    L3 = 22,
    L4 = 23,

    AlgaeProcessor = 24,
    AlgaeBarge = 25,
    
    // climbing states
    ClimbDeployed = 30,
    ClimbRetracted = 31
};

enum Auton {
    // dawg IDK what's gonna go in here yet
    Brick = 0
};


class StateMachine
{
    public:
        bool isEnabled(){return robotState > 0;};

        RobotState getRobotState(){return robotState;};
        FieldSide getFieldSide(){return fieldSide;};
        MechState getMechState(){return mechState;};
        Auton getAuto(){return auton;};

        void setRobotState(RobotState state){robotState = state;};
        void setFieldSide(FieldSide side){fieldSide = side;};
        void setMechstate(MechState state){mechState = state;};
        void setAuto(Auton autoMode){auton = autoMode;};


    private:
        RobotState robotState;
        FieldSide fieldSide;
        MechState mechState;
        Auton auton;
};
