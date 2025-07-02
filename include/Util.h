#pragma once

#include <Arduino.h>

// pose and positional stuff
struct Pose2D {
    double x; 
    double y;
    double theta; // DEGREES
};

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
