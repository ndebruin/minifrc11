#pragma once

#include <Arduino.h>

class Sensor
{
    public:
        Sensor(uint8_t SensorPin) : pin(SensorPin) {}

        void setThreshold(uint16_t thresholdValue){ threshold = thresholdValue; };

        uint8_t begin()
        {
            analogReadResolution(12); // just makes sure it is in the right mode
            // 12 bit gives us 0-4095
            return 0;
        }

        uint8_t update()
        {
            rawReading = analogRead(pin);
            state = (rawReading > threshold);
            return 0;
        }

        bool getState(){ return state; };
        uint16_t getReading(){ return rawReading; };

    private:
        uint8_t pin;
        uint16_t threshold;

        bool state;
        uint16_t rawReading;
};