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

// which side of the robot are we scoring off of?
enum ScoreSide
{
    Forward = 0,
    Backward = 1
};

// which side of the reef are we scoring on?
enum reefSide
{
    Left = 0,
    Center = 1,
    Right = 2
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
        DrivetrainOrientation getOrientation(){return drivetrainMoment;};
        Auton getAuto(){return auton;};
        ScoreSide getScoringSide(){return scoreSide;};

        void setRobotState(RobotState state){ robotState = state; };
        void setFieldSide(FieldSide side){ fieldSide = side; };
        void setAuto(Auton autoMode){ auton = autoMode; };
        void setOrientation(DrivetrainOrientation orientation){ drivetrainMoment = orientation; };
        void setScoreSide(ScoreSide Scoreside){ scoreSide = Scoreside; };


    private:
        RobotState robotState;
        FieldSide fieldSide;
        DrivetrainOrientation drivetrainMoment;
        Auton auton;
        ScoreSide scoreSide;
};
