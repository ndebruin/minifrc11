#pragma once

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
    L1Ground,
    L1EE,
    L2,
    L3,
    L4,
    GroundIntake,
    DeAlgaefy,
    StationIntake,
    Climb
};

// pose and positional stuff
struct Pose2D {
    double x; 
    double y;
    double theta; // DEGREES
};

Pose2D transformPose(Pose2D target, Pose2D addition){
    Pose2D transformedPose;
    transformedPose.x = target.x + addition.x;
    transformedPose.y = target.y + addition.y;
    transformedPose.theta = target.theta + addition.theta;
    return transformedPose;
}

Pose2D fieldToRobot(Pose2D field)
{
    Pose2D robot;
    robot.x = field.x * cos(field.theta*DEG_TO_RAD) - field.y * sin(field.theta*DEG_TO_RAD);
    robot.y = field.x * sin(field.theta*DEG_TO_RAD) + field.y * cos(field.theta*DEG_TO_RAD);
    robot.theta = field.theta;
    return robot;
}

Pose2D robotToField(Pose2D robot)
{
    Pose2D field;
    field.x = robot.x * cos(robot.theta*DEG_TO_RAD) + robot.y * sin(robot.theta*DEG_TO_RAD);
    field.y = -robot.x * sin(robot.theta*DEG_TO_RAD) + robot.y * cos(robot.theta*DEG_TO_RAD);
    field.theta = robot.theta;
    return field;

}

float floatmap(float val, float in_min, float in_max, float out_min, float out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


String printPose(Pose2D Pose){
    return "X: " + String(Pose.x) + " Y: " + String(Pose.y) + " Theta: " + String(Pose.theta);
}