#pragma once

#include <Arduino.h>
#include <Wire.h>
#include "Util.h"
#include <PestoLink-Receive.h>

#define I2C_ADDRESS 0x08
#define CMD_GET_DATA 0x01
#define CMD_RESET_POSE 0x02
#define CMD_ZERO_YAW 0x03

#define DEBUG

class OdomSensor
{

    public:
        OdomSensor(TwoWire *wireInterface = &Wire) : interface(wireInterface) {}

        uint8_t begin()
        {
            // we are gonna make them start the wire seperately
            // so this does basically nothing
            return update();
        }

        uint8_t update()
        {
            requestPose();

            return readReturnedPose();
        }

        Pose2D getPose(){ return currentPose; };

        uint8_t zeroYaw(){ requestYawReset(); return 0; };

        uint8_t resetPose(Pose2D setPose){ requestPoseReset(setPose); return 0; };

    private:
        TwoWire *interface;

        Pose2D currentPose;

        void requestPose()
        {
            interface->beginTransmission(I2C_ADDRESS);
            interface->write(CMD_GET_DATA);
            interface->endTransmission();
        }

        void requestYawReset()
        {
            interface->beginTransmission(I2C_ADDRESS);
            interface->write(CMD_ZERO_YAW);
            interface->endTransmission();
        }

        void requestPoseReset(Pose2D desiredPose)
        {
            interface->beginTransmission(I2C_ADDRESS);
            interface->write(CMD_RESET_POSE);
            interface->write((uint8_t*)&desiredPose.x, 8);
            interface->write((uint8_t*)&desiredPose.y, 8);
            interface->write((uint8_t*)&desiredPose.theta, 8);
            interface->endTransmission();
        }

        uint8_t readReturnedPose()
        {
            interface->requestFrom(I2C_ADDRESS, 25);
            if (interface->available() == 25) {
                byte status = interface->read();
                byte buffer[24];
                for (int i = 0; i < 24; i++) {
                    buffer[i] = interface->read();
                }
                double x, y, theta;
                memcpy(&x, &buffer[0], 8);
                memcpy(&y, &buffer[8], 8);
                memcpy(&theta, &buffer[16], 8);

                currentPose.x = x;
                currentPose.y = y;
                currentPose.theta = theta;


                if (status == 0x00) {
                    #ifdef DEBUG
                        // PestoLink.printTerminal("Sensor Data receieved successfully!");
                        PestoLink.printTerminal(String(y).c_str());
                    #endif
                    return 0;
                } else {
                    #ifdef DEBUG
                        PestoLink.printTerminal("Sensor returned error");
                    #endif
                    return 1;
                }
            } else {
                #ifdef DEBUG
                    PestoLink.printTerminal("Incomplete response");
                #endif
                return 2;
            }
        }

};