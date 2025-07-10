#include <Arduino.h>

// Alfredo Stuff
#include <Alfredo_NoU2.h>
// #include <BluetoothSerial.h>
// #include <AlfredoConnect.h>
#include <PestoLink-Receive.h>

#include "RobotConfig.h"
#include "../consts/PresetConstants.h"
#include "RobotState.h"
#include "Util.h"

#include "OdomInterface.h"
#include "Sensor.h"

// subsystems
// #include "Drivetrain.h"

////////////////////////////////////////////////////////////////////// Hardware Declarations //////////////////////////////////////////////////////////////////////

// not really hardware but very needed
RobotStateStorage state;

// Sensor declerations
OdomSensor odom(&Wire);
Sensor EESensor(EESensorPin);
Sensor groundSensor(GroundSensorPin);

// subsystem declerations
// Drivetrain drivetrain(&state, &odom, frontLeftMotorChannel, frontRightMotorChannel, backLeftMotorChannel, backRightMotorChannel);

// servos and roller sensor
NoU_Servo elevatorServo = NoU_Servo(elevatorServoChannel);
NoU_Servo armServo = NoU_Servo(armServoChannel, 500, 2500);
NoU_Servo climberServo = NoU_Servo(climberServoChannel);
NoU_Servo AlgaeServo = NoU_Servo(algaeArmServoChannel, 500, 2500);
NoU_Servo intakeServo = NoU_Servo(intakeServoChannel, 500, 2500);
NoU_Motor intakeEEMotor = NoU_Motor(intakeEEMotorChannel);



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
  Wire.begin();
  odom.begin();
  EESensor.begin();
  groundSensor.begin();
  groundSensor.setThreshold(GroundSensorThreshold);
  EESensor.setThreshold(EESensorThreshold);
  EESensor.setReverse(EESensorReverse);

  // configure subsystems
  configureSubsystems();
  
  // start subsystems
  // drivetrain.begin();
  
  // start advanced controllers
  

}

////////////////////////////////////////////////////////////////////// loop() //////////////////////////////////////////////////////////////////////

void loop() 
{
  asyncUpdate(); // updates all the things that need to be updated every loop regardless of anything else


}

////////////////////////////////////////////////////////////////////// Function Definitions //////////////////////////////////////////////////////////////////////

void asyncUpdate(){
  // update subsystems

  // update our pose
  

  // let advanced controllers update

  // update from driver station
  if(!PestoLink.update()){}
    // disable if we disconnect

  // }

  if(PestoLink.buttonHeld(0)){
    // intakeServo.write(intakeDeployAngle);
    // armServo.write(armL4ForwardReadyAngle);
    elevatorServo.writeMicroseconds(elevatorClearIntakePosition);
  }
  else if(PestoLink.buttonHeld(1)){
    // armServo.write(armL4ForwardScoreAngle);
  }
  else{
    // intakeServo.write(intakeStowAngle);
    armServo.write(armMiddleAngle);
    elevatorServo.writeMicroseconds(elevatorBottomPosition);
    // armServo.write(armL4ForwardReadyAngle);
  }

  if(PestoLink.buttonHeld(2)){
    intakeEEMotor.set(eeRollerIntakeSpeed);
  }
  else if(PestoLink.buttonHeld(3)){
    intakeEEMotor.set(eeRollerL1ScoreSpeed);
  }
  else{
    intakeEEMotor.set(0.0);
  }


  // update pestolink telem
  // updatePestoLink();
  groundSensor.update();
  EESensor.update();
  digitalWrite(LED, EESensor.getState());

}

double deadzone(double raw, double minValue){
  if(fabs(raw) < minValue){
    return 0.0;
  }
  return raw;
}


void configureSubsystems()
{
  // drivetrain.setKV(kV);
  // drivetrain.setTeleopInputs(driveExp, deadzoneValue);


}

void updatePestoLink(){

}