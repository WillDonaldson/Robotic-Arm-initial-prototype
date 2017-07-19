/*
 * Modify servo as detailed in instructable before running this code 
 * Connect servo to 5V, GND and digital pin 13
 */

#include <Servo.h>
Servo myServo;

void setup() {
  myServo.attach(13); 
}

void loop() {
  myServo.write(0);
  delay(6000);        //servo will rotate in one direction for 6secs
  myServo.write(180); //servo will rotate in opposite direction 
  delay(6000);
}
