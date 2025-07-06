#pragma once

#include <Arduino.h>

// what state is the robot in?
enum RobotRunState 
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





// autons!
enum Auton 
{
    // dawg IDK what's gonna go in here yet
    Brick = 0
};


class RobotStateStorage
{
    public:
        bool isEnabled(){return robotState > 0;};

        RobotRunState robotState;
        FieldSide fieldSide;
        Auton auton;
};
