#include <Arduino.h>

// Alfredo Stuff
#include <Alfredo_NoU2.h>
// #include <BluetoothSerial.h>
// #include <AlfredoConnect.h>
#include <PestoLink-Receive.h>

#include "RobotConfig.h"
#include "RobotState.h"
#include "Util.h"

#include "OdomInterface.h"
#include "Sensor.h"

// subsystems
#include "Drivetrain.h"

////////////////////////////////////////////////////////////////////// Hardware Declarations //////////////////////////////////////////////////////////////////////

// not really hardware but very needed
RobotStateStorage state;

// Sensor declerations
OdomSensor odom(&Wire);
Sensor EESensor(EESensorPin);
Sensor groundSensor(GroundSensorPin);

// subsystem declerations
Drivetrain drivetrain(&state, &odom, frontLeftMotorChannel, frontRightMotorChannel, backLeftMotorChannel, backRightMotorChannel);



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

  // Serial.begin(9600);

  // start DS comms
  PestoLink.begin(robotName);

  // start sensors
  Wire.begin();
  odom.begin();
  EESensor.begin();
  groundSensor.begin();

  // configure subsystems
  configureSubsystems();
  
  // start subsystems
  drivetrain.begin();
  // superStructure.begin();
  // intake.begin();
  // algaeArm.begin();
  // climber.begin();
  
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
  if(!PestoLink.update()){
    // disable if we disconnect
  }

  // update pestolink telem
  updatePestoLink();

}

void updatePestoLink(){
}

double deadzone(double raw, double minValue){
  if(fabs(raw) < minValue){
    return 0.0;
  }
  return raw;
}


void configureSubsystems()
{
  drivetrain.setKV(kV);
  drivetrain.setTeleopInputs(driveExp, deadzoneValue);


}