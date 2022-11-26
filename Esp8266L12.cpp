





#if defined(ESP8266)

#include <Arduino.h>
#include "Esp8266L12.h"

uint32_t Esp8266L12::_servoMap = 0;      // declaration of

// similar to map but will have increased accuracy that provides a more
// symmetrical api (call it and use result to reverse will provide the original value)
int improved_map(int value, int minIn, int maxIn, int minOut, int maxOut)
{
    const int rangeIn = maxIn - minIn;
    const int rangeOut = maxOut - minOut;
    const int deltaIn = value - minIn;
    // fixed point math constants to improve accuracy of divide and rounding
    constexpr int fixedHalfDecimal = 1;
    constexpr int fixedDecimal = fixedHalfDecimal * 2;

    return ((deltaIn * rangeOut * fixedDecimal) / (rangeIn) + fixedHalfDecimal) / fixedDecimal + minOut;
}

Esp8266L12::Esp8266L12() {
  _attached = false;
//   _valueUs = DEFAULT_NEUTRAL_PULSE_WIDTH;
//   _minUs = DEFAULT_MIN_PULSE_WIDTH;
//   _maxUs = DEFAULT_MAX_PULSE_WIDTH;
}

Esp8266L12::~Esp8266L12() {
  detach();
}

uint8_t Esp8266L12::attach(int pin_pwm_out, int pin_analog_in, int value)
{
    if (!_attached) {
        pinMode(pin_pwm_out, OUTPUT);           // pwm pin of esp8266, esp8266 output
        pinMode(pin_analog_in, INPUT);          // analog read pin of esp8266, intput to esp8266
        // set pin init voltage
        digitalWrite(pin_pwm_out, LOW);         // pull down it for init.
        // set status flags
        _pin_pwmout = pin_pwm_out;
        _pin_ana_in = pin_analog_in;
        _attached = true;
    }
    setStrokeLen(value);
    return pin_pwm_out;
}


void Esp8266L12::detach(){
    if (_attached) {
        write_blind(0);
        _attached = false;
    }
}

void Esp8266L12::setStrokeLen(int value){
    write_blind(value);
    
    // @todo: you can add closed-loop control here
}

int Esp8266L12::read(){
    int readAnaRaw = read_analogPIN();
    int readAnaMapped = improved_map(readAnaRaw, 1024, 0, 0, 99);
    Serial.printf("  esp8266 readAnalog raw value= %d, mapped value=%d\n", readAnaRaw, readAnaMapped);
    return readAnaMapped;
}

void Esp8266L12::write_blind(uint8_t percentLength){
    uint8_t realSigInt = floor(255*percentLength/100);
    Serial.printf("  setStrokeLen: realSigInt= %d\n", realSigInt);
    analogWrite(_pin_pwmout, realSigInt);

    //
    // @todo: you can add delay here, to wait for the strock's move. 
    // the speed depends on the gear ratio: 210, 150, 100, etc.
}

uint16_t Esp8266L12::read_analogPIN(void){
    return analogRead(_pin_ana_in);
}

bool Esp8266L12::attached(){
    return _attached;
}


#endif
