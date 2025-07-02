#pragma once

#include <Arduino.h>
#include <Alfredo_NoU2.h>

#include "State.h"
#include "Util.h"

#include "Constants.h"

class AlgaeArm
{
    public:
        AlgaeArm(uint8_t servoChannel) : armServo(servoChannel) {};

        uint8_t begin()
        {
            // place us into our initial state
            armServo.write(algaeStartingConfigAngle);
        }

        uint8_t update()
        {
            
        }

    private:
        NoU_Servo armServo;
};