#pragma once

#include <Arduino.h>
#include <Alfredo_NoU2.h>

#include "State.h"
#include "Util.h"

class Drivetrain
{
    public:
        Drivetrain(StateMachine* State, uint8_t frontLeftMotorChannel, uint8_t frontRightMotorChannel, uint8_t backLeftMotorChannel, uint8_t backRightMotorChannel) 
        {
            state = State;
            frontLeftMotor = NoU_Motor(frontLeftMotorChannel);
            frontRightMotor = NoU_Motor(frontRightMotorChannel);
            backLeftMotor = NoU_Motor(backLeftMotorChannel);
            backRightMotor = NoU_Motor(backRightMotorChannel);
            nou_drivetrain = NoU_Drivetrain(&frontLeftMotor, &frontRightMotor, &backLeftMotor, &backRightMotor);
        }

        void setKV(double kV){ nou_drivetrain.setMinimumOutput(kV); _kV = kV; };


        void stop(){
            nou_drivetrain.holonomicDrive(0.0, 0.0, 0.0);
        }


    private:
        StateMachine* state;
        NoU_Motor frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor;
        NoU_Drivetrain nou_drivetrain;

        double _kV;

};