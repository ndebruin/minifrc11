#pragma once

#include <Arduino.h>
#include <Alfredo_NoU2.h>
#include "RobotConfig.h"
#include "RobotState.h"
#include "Sensor.h"
#include "OdomInterface.h"

struct Context {
    // actuators
    NoU_Servo elevatorServo;
    NoU_Servo armServo;
    NoU_Servo climberServo;
    NoU_Servo AlgaeServo;
    NoU_Servo intakeServo;
    NoU_Motor intakeEEMotor;

    // Sensors
    Sensor eeSensor;
    Sensor groundSensor;

    // other state storage stuff
    RobotStateStorage robotStateStorage;

    // Odom
    OdomSensor odomSensor;

    // most other stuff (values for actuators) 
    // is pulled from "PresetConstants.h"
};