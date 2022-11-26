/* ESP8266 control the L12 Actuonix Linear Actuator (L12-p model) with the library "Esp8266L12"
 * connect A0(ESP8266 chip) to the analog position feedback pin of L12
 * connect D8(ESP8266 IO15) to the voltage control pin of L12
 * Tested on wemos_esp8266_D1_mini board.
 * 
 * date: 2022-11-26 21:05:27
 * author: sonictl
 * 
*/

#include <Arduino.h>

#include "Esp8266L12.h"

#define ACT_ANA_IN A0
#define PWM_OUT D8

Esp8266L12 actuator;
int loop_count = 0;

void setup(){
    Serial.begin(9600);     // init Serial device
    actuator.attach(PWM_OUT, ACT_ANA_IN, 50);     // attaches the servo on pin to the servo object

    delay(5000);   // wait for the stroke reaching the init position
}

void loop(){
    Serial.printf("****\nloop_count: %d\n", loop_count++);

    Serial.printf("  servoExt read value= %d\n", actuator.read());

    if (loop_count % 3 == 0){
        actuator.setStrokeLen(80);
    }

    if (loop_count % 7 == 0){
        actuator.setStrokeLen(1);
    }

    delay(5000);

}