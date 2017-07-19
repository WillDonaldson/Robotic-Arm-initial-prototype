/*
 * Connect servo to 5V, GND and digital pin 13
 */
 
#include <Servo.h>
Servo wristServo;

void setup() {
  Serial.begin(9600);
  wristServo.attach(13);
  wristServo.write(90);
  Serial.println("Servo moved to 90 degrees");
}

void loop() {
}
