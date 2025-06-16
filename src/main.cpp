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
StateMachine state;

////////////////////////////////////////////////////////////////////// Function Declerations //////////////////////////////////////////////////////////////////////

void asyncUpdate();

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

  PestoLink.begin(robotName);

  // start RSL
  RSL::initialize();

  // start subsystems


  // start our pose estimator
  
  
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


  // rsl code
  RSL::update();

  // if(state.isEnabled()){
  //   RSL::setState(RSL_ENABLED);
  // }
  // else if(!state.isEnabled()){
  //   RSL::setState(RSL_OFF);
  // }

}

void updatePestoLink(){
}

double deadzone(double raw, double minValue){
  if(fabs(raw) < minValue){
    return 0.0;
  }
  return raw;
}



