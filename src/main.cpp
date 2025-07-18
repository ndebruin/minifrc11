#include <Arduino.h>

// Alfredo Stuff
#include <Alfredo_NoU2.h>
// #include <BluetoothSerial.h>
// #include <AlfredoConnect.h>
#include <PestoLink-Receive.h>

#include "RobotConfig.h"
#include "../consts/PresetConstants.h"
#include "../consts/DrivetrainTuning.h"
#include "RobotState.h"
#include "Util.h"

// #include "OdomInterface.h"
#include "Sensor.h"

// state machine
// #include "Context.h"
// #include "../boilerplate/StateMachine/StateMachine.h"
// #include "../include/States/States.h"

// subsystems
#include "DrivetrainController.h"
#include "InputParser.h"

#include "Transforms.h"
#include "GeoHelper.h"

////////////////////////////////////////////////////////////////////// Hardware Declarations //////////////////////////////////////////////////////////////////////

// not really hardware but very needed
RobotStateStorage state;
InputParser inputParser (robotName, &state);

// Sensor declerations
// OdomSensor odom(&Wire);
Sensor EESensor(EESensorPin);
Sensor groundSensor(GroundSensorPin);

// subsystem declerations
// DrivetrainController drivetrain = DrivetrainController(&state, &odom, frontLeftMotorChannel, frontRightMotorChannel, backLeftMotorChannel, backRightMotorChannel);
NoU_Motor frontLeftMotor(frontLeftMotorChannel);
NoU_Motor frontRightMotor(frontRightMotorChannel);
NoU_Motor backLeftMotor(backLeftMotorChannel);
NoU_Motor backRightMotor(backRightMotorChannel);

NoU_Drivetrain drivetrain(&frontLeftMotor, &frontRightMotor, &backLeftMotor, &backRightMotor);


// servos and roller sensor
NoU_Servo elevatorServo = NoU_Servo(elevatorServoChannel);
NoU_Servo armServo = NoU_Servo(armServoChannel, 500, 2500);
NoU_Servo climberServo = NoU_Servo(climberServoChannel);
NoU_Servo AlgaeServo = NoU_Servo(algaeArmServoChannel, 500, 2500);
NoU_Servo intakeServo = NoU_Servo(intakeServoChannel, 500, 2500);
NoU_Motor intakeEEMotor = NoU_Motor(intakeEEMotorChannel);

// Context ctx = {
//   .elevatorServo = elevatorServo,
//   .armServo = armServo,
//   .climberServo = climberServo,
//   .AlgaeServo = AlgaeServo,
//   .intakeServo = intakeServo,
//   .intakeEEMotor = intakeEEMotor,
//   .eeSensor = EESensor,
//   .groundSensor = groundSensor,
//   .robotStateStorage = state,
//   // .odomSensor = odom,
//   .inputs = inputParser
// };

// StateMachine stateMachine(new StowedEmpty(&ctx));



////////////////////////////////////////////////////////////////////// Function Declerations //////////////////////////////////////////////////////////////////////

void asyncUpdate();
void configureSubsystems();

double deadzone(double raw, double minValue);
void constantButtons();
void runDrivetrain();
void runStateSelector(); 

void updatePestoLink();

////////////////////////////////////////////////////////////////////// Global Variables //////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////// setup() //////////////////////////////////////////////////////////////////////

void setup()
{
  // start up bluetooth link for alfredoconnect
  // SerialBluetooth.begin(robotName);
  // AlfredoConnect.begin(SerialBluetooth);

  pinMode(LED, OUTPUT);

  // start DS comms
  PestoLink.begin(robotName);

Serial.begin(9600);

  // start sensors
  // Wire.begin();
  // odom.begin();
  EESensor.begin();
  groundSensor.begin();
  groundSensor.setThreshold(GroundSensorThreshold);
  EESensor.setThreshold(EESensorThreshold);
  EESensor.setReverse(EESensorReverse);

  AlgaeServo.write(algaeStartingConfigAngle);
  drivetrain.setInputExponent(1.5);

  // configure subsystems
  // configureSubsystems();
  
  // start subsystems
  // drivetrain.setInversions(false, true, false, true);

  frontLeftMotor.setInverted(false);
  frontRightMotor.setInverted(true);
  backLeftMotor.setInverted(false);
  backRightMotor.setInverted(true);

  
  // start advanced controllers
  // stateMachine.initialize();

}

////////////////////////////////////////////////////////////////////// loop() //////////////////////////////////////////////////////////////////////

void loop() 
{
  asyncUpdate(); // updates all the things that need to be updated every loop regardless of anything else
  // PestoLink.printTerminal(printPose(odom.getPose()).c_str());
  digitalWrite(LED, (groundSensor.getState() || EESensor.getState()));
  // delay(10);

}
unsigned long startTime;


int target;
////////////////////////////////////////////////////////////////////// Function Definitions //////////////////////////////////////////////////////////////////////

void asyncUpdate(){
  // update subsystems

  // update our pose
  groundSensor.update();
  EESensor.update();
  // odom.update();
  

  // let advanced controllers update

  // drivetrain.update();
  // stateMachine.loop();
  
  
  inputParser.update();

  Pose2D driverInput = inputParser.getDrivetrainControls();

  double omega = driverInput.theta;
  // if(false){
  //   driverInput.theta = odom.getPose().theta*DEG_TO_RAD;
  //   driverInput = fieldToRobot(driverInput);
  // }
  if(state.isEnabled()){
    if(PestoLink.buttonHeld(buttonL4)){
      target = 4;
    }
    else if(PestoLink.buttonHeld(buttonL3)){
      target = 3;
    }
    else if(PestoLink.buttonHeld(buttonL2)){
      target = 2;
    }
    else if(PestoLink.buttonHeld(buttonL1)){
      target = 1;
    }
    drivetrain.holonomicDrive(driverInput.x, driverInput.y, driverInput.theta);

      if(PestoLink.buttonHeld(buttonExecRight)){
        if(target == 4){
          elevatorServo.writeMicroseconds(elevatorL4Position);
          armServo.write(armL4ForwardReadyAngle);
        }
        else if(target == 3){
          elevatorServo.writeMicroseconds(elevatorBottomPosition);
          armServo.write(armL3ForwardReadyAngle);
        }
        else if(target == 2){
          elevatorServo.writeMicroseconds(elevatorBottomPosition);
          armServo.write(armL2ForwardReadyAngle);
        }
        else if(target == 1){
          elevatorServo.writeMicroseconds(elevatorBottomPosition);
          armServo.write(armL1FowardAngle);
          // intakeEEMotor.set(eeRollerL1ScoreSpeed);
        }
      
      intakeServo.write(intakeStowAngle);
    }
    else if(PestoLink.buttonHeld(buttonExecLeft)){
      elevatorServo.writeMicroseconds(elevatorBottomPosition);
      AlgaeServo.write(algaeInitialDeployAngle);
    }
    else if(PestoLink.buttonHeld(3)){
      elevatorServo.writeMicroseconds(elevatorDeAlgaeL3Position);
      AlgaeServo.write(algaeInitialDeployAngle);
    }
    else if(PestoLink.buttonHeld(2)){
      armServo.write(armL1FowardAngle);
      elevatorServo.writeMicroseconds(elevatorBottomPosition);
      
      intakeServo.write(intakeDeployAngle);
      climberServo.writeMicroseconds(climberDeployAngle);
      AlgaeServo.write(algaeStartingConfigAngle);
    }
    else if(PestoLink.buttonHeld(0)){
      armServo.write(armL1FowardAngle);
      elevatorServo.writeMicroseconds(elevatorBottomPosition);
      
      intakeServo.write(intakeDeployAngle);
      climberServo.writeMicroseconds(climberClimbAngle);
      AlgaeServo.write(algaeStartingConfigAngle);
    }

    else if(PestoLink.buttonHeld(buttonGroundIntake) && !groundSensor.getState()){
    elevatorServo.writeMicroseconds(elevatorClearIntakePosition);
    intakeServo.write(intakeDeployAngle);
    intakeEEMotor.set(intakeRollerIntakeSpeed);
  }
  // else if(PestoLink.buttonHeld(buttonGroundIntake) && groundSensor.getState()){
  //   elevatorServo.writeMicroseconds(elevatorHandoffHighPosition);
  //   intakeServo.write(intakeHandoffAngle);
  // }

  else if(PestoLink.buttonHeld(buttonDeAlgae)){
    elevatorServo.writeMicroseconds(elevatorHandoffLowPosition);
    intakeEEMotor.set(rollerEEHandoffSpeed);
    intakeServo.write(intakeHandoffAngle);
  }
  else{
    elevatorServo.writeMicroseconds(elevatorHandoffHighPosition);
    armServo.write(armMiddleAngle);
    intakeEEMotor.set(0.0);
    intakeServo.write(intakeStowAngle);
    AlgaeServo.write(algaeStowAngle);
    climberServo.writeMicroseconds(climberStowAngle);
  }


  
  }
  else{
    drivetrain.holonomicDrive(0.0,0.0,0.0);
    elevatorServo.writeMicroseconds(elevatorBottomPosition);
    AlgaeServo.write(algaeStartingConfigAngle);
    
  }
  

  // if(PestoLink.buttonHeld(8)){
  //   odom.zeroYaw();
  // }

  // if(PestoLink.buttonHeld(buttonGroundIntake) && !groundSensor.getState()){
  //   // elevatorServo.writeMicroseconds(elevatorClearIntakePosition);
  //   // armServo.write(armL1FowardAngle);
  //   intakeServo.write(intakeDeployAngle);
  //   intakeEEMotor.set(intakeRollerIntakeSpeed);
  // }
  // else{
  //   intakeServo.write(intakeStowAngle);
  //   intakeEEMotor.set(0.0);
  //   // elevatorServo.writeMicroseconds(elevatorBottomPosition);
  // }

  // if(PestoLink.buttonHeld(buttonExecLeft)){
  //   intakeServo.write(intakeL1ReadyAngle);
  //   // intakeEEMotor.set(intakeRollerL1ScoreSpeed);
  // }
  // else if(PestoLink.buttonHeld(buttonExecRight)){
  //   intakeServo.write(intakeL1ScoreAngle);
  //   intakeEEMotor.set(intakeRollerL1ScoreSpeed);
  // }

  // if(PestoLink.buttonHeld(buttonDeAlgae)){
  //   startTime = millis();
  //   AlgaeServo.write(algaeInitialDeployAngle);
  //   if(millis() - startTime > 1000){
  //     AlgaeServo.write(algaeFinalDeployAngle);
  //   }
  // }



  

  // PestoLink.printTerminal(String(driverInput.x).c_str());





  // drivetrain.teleopDrive(inputParser.getDrivetrainControls());

  // drivetrain.teleopDrive(Pose2D{0.0,0.0,0.0});

  // PestoLink.printTerminal(printPose(inputParser.getDrivetrainControls()).c_str());

  // if(state.robotState == RobotRunState::Auto){
  //   switch(state.auton){
  //     case Brick:
  //       break;
  //     // case Taxi:
  //     //   drivetrain.startAutoalign(
  //     //     transformPose(
  //     //       transformPose(
  //     //         ReefBranchDRight, armL3ForwardToRobotTransform)
  //     //         , robotToSensorTransform));
  //     //     if(drivetrain.isInPosition()){
  //     //       drivetrain.stop();
  //     //       break;
  //     //     }
  //     //   break;
  //   };
  // }



  // if(PestoLink.buttonHeld(0)){
  //   // climberServo.writeMicroseconds(climberDeployAngle);
  //   // intakeServo.write(intakeDeployAngle);
  //   // intakeEEMotor.set(0.0);
  //   // armServo.write(armL2ForwardReadyAngle);
  //   // AlgaeServo.write(algaeInitialDeployAngle);
  //   elevatorServo.writeMicroseconds(elevatorL4Position);

  // }
  // else if(PestoLink.buttonHeld(1)){
  //   // climberServo.writeMicroseconds(climberClimbAngle);
  //   // intakeServo.write(intakeL1ScoreAngle);
  //   // intakeEEMotor.set(intakeRollerL1ScoreSpeed);
  //   // armServo.write(armL4ForwardScoreAngle);
  //   elevatorServo.writeMicroseconds(elevatorDeAlgaeL3Position);
  //   // AlgaeServo.write(algaeStowAngle);
  // }
  // else{
  //   // intakeServo.write(intakeStowAngle);
  //   // intakeEEMotor.set(0.0);
  //   // armServo.write(armMiddleAngle);
  //   elevatorServo.writeMicroseconds(elevatorBottomPosition);
  //   // armServo.write(armL4ForwardReadyAngle);
  //   // AlgaeServo.write(algaeStartingConfigAngle);
  // }

  // if(PestoLink.buttonHeld(2)){
  //   // intakeEEMotor.set(eeRollerIntakeSpeed);
  //   // climberServo.writeMicroseconds(climberStowAngle);
  // }
  // else if(PestoLink.buttonHeld(3)){
  //   // intakeEEMotor.set(eeRollerL1ScoreSpeed);
  //   // climberServo.writeMicroseconds(climberStowAngle);
  // }
  // else{
  //   intakeEEMotor.set(0.0);
  // }


  // update pestolink telem
  // updatePestoLink();

  // digitalWrite(LED, groundSensor.getState());

}

double deadzone(double raw, double minValue){
  if(fabs(raw) < minValue){
    return 0.0;
  }
  return raw;
}


void updatePestoLink(){

}