#pragma once

#include <Arduino.h>

// what state is the robot in?
enum RobotRunState 
{
    ESTOP = -1,
    Disabled = 0,
    Teleop = 1,
    Auto = 2
};

// basic configuration
enum FieldSide 
{
    Blue = 0,
    Red = 1
};

// autons!
enum Auton 
{
    // dawg IDK what's gonna go in here yet
    Brick,
    Taxi,

    L4SingleCenter,
    L1SingleCenter,
    
    L4SingleProcessorSide,
    L4SingleBargeSide,
    
    L4DoubleProcessorSide,
    L4DoubleBargeSide,
};


class RobotStateStorage
{
    public:
        bool isEnabled(){return robotState > 0;};

        RobotRunState robotState;
        FieldSide fieldSide;
        Auton auton;
};
