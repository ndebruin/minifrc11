#pragma once

#include <Arduino.h>
#include <Alfredo_NoU2.h>

#include "RobotState.h"
#include "Util.h"
#include "../boilerplate/Utilities/PIDController.h"
#include "OdomInterface.h"

#include "../consts/DrivetrainTuning.h"

class DrivetrainController 
{
public:
    DrivetrainController(RobotStateStorage* RobotState, OdomSensor* OdomSensor, uint8_t frontLeftMotorChannel, uint8_t frontRightMotorChannel, uint8_t backLeftMotorChannel, uint8_t backRightMotorChannel)
            : robotState(RobotState), odomSensor(OdomSensor), 
                frontLeftMotor(frontLeftMotorChannel), frontRightMotor(frontRightMotorChannel), backLeftMotor(backLeftMotorChannel), backRightMotor(backRightMotorChannel),
                nou_drivetrain(&frontLeftMotor, &frontRightMotor, &backLeftMotor, &backRightMotor),
                xController(linX_kP, linX_kI, linX_kD, -1.0, 1.0),
                yController(linY_kP, linY_kI, linY_kD, -1.0, 1.0),
                thetaController(angZ_kP, angZ_kI, angZ_kD, -1.0, 1.0)
                {};


    void setKV(double kV){ nou_drivetrain.setMinimumOutput(kV); _kV = kV; };
    void setTeleopInputs(double exp, double deadband){ inputExponent = exp; inputDeadband = deadband; };

    void setInversions(bool FL, bool FR, bool BL, bool BackR){
        frontLeftMotor.setInverted(FL);
        frontRightMotor.setInverted(FR);
        backLeftMotor.setInverted(BL);
        backRightMotor.setInverted(BackR);
    };

    void stop()
    {
        command.x = 0.0; command.y = 0.0; command.theta = 0.0;
        autoAligning = false;
        applyCommand();
    };

    void update(){
        // disable status
        if(robotState->isEnabled() == false){
            stop();
            return;
        }

        // if currently running an autoalign command
        if(autoAligning){
            driveToTarget();
        }

        applyCommand();
    }

    void setTeleopFieldOriented(bool FieldOriented){ fieldOriented = FieldOriented; };
    
    void teleopDrive(Pose2D driverInput)
    {
        // early return protecting from auto
        if(robotState->robotState == RobotRunState::Auto){
            return;
        }
        double omega = driverInput.theta;
        if(fieldOriented){
            driverInput.theta = odomSensor->getPose().theta*DEG_TO_RAD;
            driverInput = fieldToRobot(driverInput);
        }
        command.x = applyInputCurve(driverInput.x);
        command.y = applyInputCurve(driverInput.y);
        command.theta = applyInputCurve(omega);
    };

    void startAutoalign(Pose2D target){
        TargetPose = target;
        autoAligning = true;
    }

    void stopAutoalign(){ autoAligning = false; };

    bool isInPosition(){ return inPosition; };

private:
    NoU_Motor frontLeftMotor, frontRightMotor, backLeftMotor, backRightMotor;
    NoU_Drivetrain nou_drivetrain;
    RobotStateStorage* robotState;

    OdomSensor* odomSensor;

    PIDController xController;
    PIDController yController;
    PIDController thetaController;

    bool autoAligning;
    bool inPosition;

    double _kV;
    // teleop params
    double inputExponent;
    double inputDeadband;
    bool fieldOriented = false;
    
    Pose2D command; // ROBOT RELATIVE

    Pose2D TargetPose; // FIELD RELATIVE

    // apply deadbanding, minimum output, and input exponentiation for teleop driving
    float applyInputCurve(float input)
    {
        return floatmap((fabs(input) < inputDeadband ? 0 : 1) // apply deadband
                * pow(max(floatmap(constrain(fabs(input), -1, 1), inputDeadband, 1, 0, 1), 0.0f), inputExponent), // account for deadband, apply exponent
                0, 1, _kV, 1.0) // apply minimum and maximum output limits
            * (input == 0 ? 0 : input > 0 ? 1 : -1) // apply original sign
            ;
    }

    void applyCommand()
    {
        nou_drivetrain.holonomicDrive(command.x, command.y, command.theta);
    }

    void driveToTarget() {

        Pose2D currentPose = odomSensor->getPose();

        Pose2D newCommand;
        
        newCommand.x = xController.compute(TargetPose.x, currentPose.x, millis());
        newCommand.y = yController.compute(TargetPose.y, currentPose.y, millis());
        newCommand.theta = thetaController.compute(TargetPose.theta, currentPose.theta, millis());

        // here is where i would apply feedforward if i cared

        // check error
        double xError = TargetPose.x - currentPose.x;
        double yError = TargetPose.y - currentPose.y;
        double thetaError = TargetPose.theta - currentPose.theta;
        // if all are good
        if((fabs(xError) < x_AcceptableError) && (fabs(yError) < y_AcceptableError) && (fabs(thetaError) < theta_AcceptableError)){
            inPosition = true;
        }
    }
};

