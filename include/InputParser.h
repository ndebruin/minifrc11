#pragma once

// this class is responsible for taking joystick data and turning it into controls for the actual robot state machine to use.

#include <Arduino.h>
#include <PestoLink-Receive.h>
#include "Util.h"
#include "RobotConfig.h"
#include "RobotState.h"


class InputParser
{
public:
    InputParser(const char* btName, RobotStateStorage* stateStorage) : btname(btName), state(stateStorage) {};


    void begin(){
        PestoLink.begin(btname);
    };
    
    bool update()
    {
        bool pestoStatus = PestoLink.update();

        joystickValues.x = PestoLink.getAxis(axisLinX);
        joystickValues.y = PestoLink.getAxis(axisLinY);
        joystickValues.theta = PestoLink.getAxis(axisAngZ);

        // reef selection
        if(PestoLink.buttonHeld(buttonL1)){ goalLocationY = L1Trough; }
        else if(PestoLink.buttonHeld(buttonL2)){ goalLocationY = L2Branch; }
        else if(PestoLink.buttonHeld(buttonL3)){ goalLocationY = L3Branch; }
        else if(PestoLink.buttonHeld(buttonL4)){ goalLocationY = L4Branch; }

        

        // execute buttons
        if(PestoLink.buttonHeld(buttonExecLeft)){
            // left or center
            if(goalLocationY == L1Trough){
                goal = L1Ground;
                goalLocationX = Center;
            }
            else{ 
                goalLocationX = Left;
                if(goalLocationY == L2Branch){ goal = L2; };
                if(goalLocationY == L3Branch){ goal = L3; };
                if(goalLocationY == L4Branch){ goal = L4; };
            };
            execute = true;
        }
        else if(PestoLink.buttonHeld(buttonExecRight)){
            // left or center
            if(goalLocationY == L1Trough){
                goal = L1EE;
                goalLocationX = Center;
            }
            else{ 
                goalLocationX = Right;
                if(goalLocationY == L2Branch){ goal = L2; };
                if(goalLocationY == L3Branch){ goal = L3; };
                if(goalLocationY == L4Branch){ goal = L4; };
            };
            execute = true;
        }
        // other buttons that self exec
        else if(PestoLink.buttonHeld(buttonDeAlgae)){
            goal = DeAlgaefy;
            execute = true;
        }
        else if(PestoLink.buttonHeld(buttonGroundIntake)){
            goal = GroundIntake;
            execute = true;
        }
        else if(PestoLink.buttonHeld(buttonStationIntake)){
            goal = StationIntake;
            execute = true;
        }
        else if(PestoLink.buttonHeld(buttonTriggerClimb)){
            goal = Climb;
            execute = true;
        }
        // stops execing if no buttons are released
        else{
            execute = false;
        }

        if(PestoLink.keyHeld(Key::Space)){
            state->robotState = RobotRunState::Disabled;
        }

        if(PestoLink.keyHeld(Key::Enter)){
            state->robotState = RobotRunState::Teleop;
        }

        if(PestoLink.keyHeld(Key::Q)){
            state->robotState = RobotRunState::Auto;
            state->auton = Auton::Taxi;
        }

        return pestoStatus;
    }

    bool shouldExecute(){ return execute; };

    ReefSide getGoalPole(){ return goalLocationX; };
    Goal getGoal(){ return goal; }
    Pose2D getDrivetrainControls(){ return joystickValues; };

private:
    
    ReefSide goalLocationX;
    ReefHeight goalLocationY;

    Goal goal;

    Pose2D joystickValues;

    const char* btname;

    bool execute;
    
    RobotStateStorage* state;

};
