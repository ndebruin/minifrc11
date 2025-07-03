#pragma once

#include <Arduino.h>
#include <Alfredo_NoU2.h>

#include "RobotState.h"
#include "Util.h"
#include "OdomInterface.h"

class Drivetrain
{
    public:
        Drivetrain(StateStorage* State, OdomSensor* odometry, uint8_t frontLeftMotorChannel, uint8_t frontRightMotorChannel, uint8_t backLeftMotorChannel, uint8_t backRightMotorChannel)
            : frontLeftMotor(frontLeftMotorChannel), frontRightMotor(frontRightMotorChannel), backLeftMotor(backLeftMotorChannel), backRightMotor(backRightMotorChannel), 
              state(State), odom(odometry), nou_drivetrain(&frontLeftMotor, &frontRightMotor, &backLeftMotor, &backRightMotor) {};


        void setKV(double kV){ nou_drivetrain.setMinimumOutput(kV); _kV = kV; };
        void setTeleopInputs(double exp, double deadband){ inputExponent = exp; inputDeadband = deadband; };

        void stop(){ nou_drivetrain.holonomicDrive(0.0, 0.0, 0.0); };

        void begin()
        {
            
        }

        void update()
        {

        }

        void teleopDrive(Pose2D driverInput)
        {
            if(state->getOrientation() == DrivetrainOrientation::FieldOriented){
                // create pose2d for just changing translations to robot oriented
                Pose2D robotRelativeTranslation;
                robotRelativeTranslation.x = driverInput.x;
                robotRelativeTranslation.y = driverInput.y;
                robotRelativeTranslation.theta = odom->getPose().theta;
                robotRelativeTranslation = fieldToRobot(robotRelativeTranslation);
                driverInput.x = robotRelativeTranslation.x;
                driverInput.y = robotRelativeTranslation.y;
            }

            command.x = applyInputCurve(driverInput.x);
            command.y = applyInputCurve(driverInput.y);
            command.theta = applyInputCurve(driverInput.theta);

            // applyCommand(); // do i actually want this?
        };

    private:
        StateStorage* state;
        OdomSensor* odom;
        NoU_Motor frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor;
        NoU_Drivetrain nou_drivetrain;

        double _kV;

        double inputExponent;
        double inputDeadband;

        Pose2D command; // ROBOT RELATIVE

        // apply deadbanding and input exponentiation for teleop driving
        float applyInputCurve(float input)
        {
            return (fabs(input) < inputDeadband ? 0 : 1) // apply deadband
            * pow(max(floatmap(constrain(fabs(input), -1, 1), inputDeadband, 1, 0, 1), 0.0f), inputExponent) // account for deadband, apply exponent
            * (input > 0 ? 1 : -1); // apply original sign
        }

        void applyCommand()
        {
            nou_drivetrain.holonomicDrive(command.x, command.y, command.theta);
        }

};