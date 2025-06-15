#pragma once

#define robotName "Team 43"

////////////////////////////////////////////////////////////////////// Drivetrain //////////////////////////////////////////////////////////////////////

#define frontLeftMotorChannel 5
#define frontRightMotorChannel 1
#define backLeftMotorChannel 6
#define backRightMotorChannel 2 

#define kS 0.7 // minimum value to overcome friction 
               // determined experimentally

#define driveExp 1.5 // control "squaring" value to get more control at the low end

#define correctCount 10

// strafe parameters
#define linX_kS 0.1 //0.01
#define linX_kP 0.05 //0.01
#define linX_kI 0.0
#define linX_kD 0.0

#define x_AcceptableError 0.2 // inches

// forward back parameters
#define linY_kS 0.1 //0.01
#define linY_kP 0.05 //0.01
#define linY_kI 0.0
#define linY_kD 0.0

#define y_AcceptableError 0.2 // inches

// turn parameters
#define angZ_kS 0.001
#define angZ_kP 0.000000000000000000001
#define angZ_kI 0.0
#define angZ_kD 0.0

#define theta_AcceptableError 10.0 // degrees


////////////////////////////////////////////////////////////////////// Controller //////////////////////////////////////////////////////////////////////

#define deadzoneValue 0.1

#define axisLinY 1
#define axisLinX 0
#define axisAngZ 2



////////////////////////////////////////////////////////////////////// Pose Estimator //////////////////////////////////////////////////////////////////////
#define DPI 600.0 // 250 Dots per inch NEED TO TUNE

constexpr float MOUSE_CONVERSION_FACTOR = (1.0/DPI); 

#define baudRate 115200
