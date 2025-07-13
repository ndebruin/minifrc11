#ifndef UTIL_h

#define UTIL_h

#include <Arduino.h>

// which side of the robot are we scoring off of?
enum ScoreSide
{
    Forward = 0,
    Backward = 1
};

// where on the reef are we scoring on?
enum ReefSide
{
    Left,
    Center,
    Right
};

enum ReefHeight
{
    L1Trough,
    L2Branch,
    L3Branch,
    L4Branch
};

enum Goal
{
    L1Ground = 0,
    L1EE =1,
    L2 = 2,
    L3 = 3,
    L4 = 4,
    GroundIntake =5,
    DeAlgaefy = 6,
    StationIntake = 7,
    Climb = 8
};

// pose and positional stuff
struct Pose2D {
    double x; 
    double y;
    double theta; // DEGREES
};

String printPose(Pose2D Pose);
float floatmap(float val, float in_min, float in_max, float out_min, float out_max);
Pose2D robotToField(Pose2D robot);
Pose2D fieldToRobot(Pose2D field);
Pose2D transformPose(Pose2D target, Pose2D addition);

#endif