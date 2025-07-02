#include <Arduino.h>

// Alfredo Stuff
#include <Alfredo_NoU2.h>
// #include <BluetoothSerial.h>
// #include <AlfredoConnect.h>
#include <PestoLink-Receive.h>

#include "Constants.h"
#include "State.h"

////////////////////////////////////////////////////////////////////// Hardware Declarations //////////////////////////////////////////////////////////////////////

// BluetoothSerial SerialBluetooth; // bluetooth link


// not really hardare but very needed
StateStorage state;

NoU_Servo algaeArm(algaeArmServoChannel);
// NoU_Servo climberServo(climberServoChannel);

////////////////////////////////////////////////////////////////////// Function Declerations //////////////////////////////////////////////////////////////////////

void asyncUpdate();

double deadzone(double raw, double minValue);
void constantButtons();
void runDrivetrain();
void runStateSelector(); 

void updatePestoLink();

////////////////////////////////////////////////////////////////////// Global Variables //////////////////////////////////////////////////////////////////////


constexpr double degreeToUS = (2500.0-500.0)/(300.0);

////////////////////////////////////////////////////////////////////// setup() //////////////////////////////////////////////////////////////////////

void setup()
{
  // start up bluetooth link for alfredoconnect
  // SerialBluetooth.begin(robotName);
  // AlfredoConnect.begin(SerialBluetooth);

  // Serial.begin(9600);

  PestoLink.begin(robotName);

  // start subsystems
  

  // start our pose estimator
  
  
  // start advanced controllers
  

}

////////////////////////////////////////////////////////////////////// loop() //////////////////////////////////////////////////////////////////////

void loop() 
{
  asyncUpdate(); // updates all the things that need to be updated every loop regardless of anything else

  // if(PestoLink.buttonHeld(0)){
  //   climberServo.writeMicroseconds(1000);
  // }
  // if(PestoLink.buttonHeld(1)){
  //   climberServo.writeMicroseconds(2500);
  // }
  if(PestoLink.buttonHeld(0)){
    algaeArm.writeMicroseconds(1510);
  }
  if(PestoLink.buttonHeld(1)){
    algaeArm.writeMicroseconds(2000);
  }



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



