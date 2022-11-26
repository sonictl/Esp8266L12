/***
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License.
 * 
 * 
*/


#ifndef Esp8266L12_h
#define Esp8266L12_h

#include <Arduino.h>

// The following values are in us (microseconds).
// Since the defaults can be overwritten in the new attach() member function,
// they were modified from the Arduino AVR Servo lib to be in the safe range

// #define DEFAULT_MIN_PULSE_WIDTH      10  // uncalibrated default, the shortest duty cycle sent to a servo
// #define DEFAULT_MAX_PULSE_WIDTH      999 // uncalibrated default, the longest duty cycle sent to a servo 
// #define DEFAULT_NEUTRAL_PULSE_WIDTH  10  // default duty cycle when servo is attached


#if !defined(ESP8266)
#error "This library only supports esp8266 boards."
#endif

class Esp8266L12
{
    public:
        Esp8266L12();
        ~Esp8266L12();

        /**
         * @brief attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure.
         *        
         * @param pin_pwm_out - esp8266 output 1k hz pwm on this pin
         * @param pin_analog_in - esp8266 read Analog signal on this pin
         * @param value - the initial value to set the stroke length, 0-99
         * @return uint8_t , returns channel number or 0 if failure.
         */
        uint8_t attach(int pin_pwm_out, int pin_analog_in, int value);

        void detach();

        void setStrokeLen(int value);             // 0-100 percentage of stroke length
        int read();                        // returns current A0 input, map AnalogRead[1024,0] to [0,99]
        void write_blind(uint8_t percentLength);  // open-loop(blindly) set stroke length with 1-100%, percentLength=[1,100]
        uint16_t read_analogPIN(void);
        bool attached();                   // return true if this servo is attached, otherwise false 


    private:
        static uint32_t _servoMap;
        bool     _attached;
        uint8_t  _pin_pwmout;
        uint8_t  _pin_ana_in;
        // uint16_t _minUs;                   
        // uint16_t _maxUs;                   
        // uint16_t _valueUs;
};

#endif


