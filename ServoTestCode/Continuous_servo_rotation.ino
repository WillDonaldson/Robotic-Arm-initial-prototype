/*
 * Modify servo as detailed in Instructable before running this code 
 * Connect servo to 5V, GND and digital pin 13
 */

#include <Servo.h>
Servo myServo;

void setup() {
  myServo.attach(13); 
}

void loop() {
  myServo.write(0);
  delay(6000);        //servo will continuously rotate in one direction for 6secs
  myServo.write(180); //servo will continuously rotate in opposite direction for 6secs
  delay(6000);
}
