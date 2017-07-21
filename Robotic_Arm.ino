/*
 * Youtube video: (ADD LINK BEFORE PUBLISHING)
 * Instructable: (ADD LINK BEFORE PUBLISHING)
 * 
 * Wiring:
 * A0 Middle finger potentiometer 
 * 6  Thumb momentary switch
 * 7  Index finger contraction servo
 * 8  Thumb contraction servo (current design does not have a position reading, need to use momentary switch on pin 6)
 * 9  Middle contraction servo (needs pot at A0 to get position reading)
 * 10 Thumb rotation servo 
 * 11 Up/Down wrist rotation servo
 * 12 Left/Right wrist rotation servo
 * 13 Ring and Pinky contraction servo
 * (all wired in parallel to 5V and GND)
 */

#include <Servo.h>

Servo ThumbRot, ThumbContract, Index, Mid, PinkyRing, UDwrist, LRwrist;   //servos  
const int Midpot=A0;        //middle finger potentiometer is connected to A0
const int ThumbButton=6;

int pos, Mpot, angleMid, buttonState; 
int MidExtd, MidCont; //the readings of the potentiometer when the middle finger is contracted and extended

void setup() {
  Serial.begin(9600);
  
  Index.attach(7);              //attaches the servo to respective pin
  ThumbContract.attach(8);
  Mid.attach(9);
  ThumbRot.attach(10);  
  UDwrist.attach(11);           
  LRwrist.attach(12);
  PinkyRing.attach(6);

  Serial.println("Need to calibrate range of middle finger potentiometer");
  Serial.println("Please rotate finger so it is at rest, fully extended");
  delay(2000);
  MidExtd=(analogRead(Midpot));
  Serial.println("Please rotate finger so it is bent over, fully contracted");
  delay(2000);
  MidCont=(analogRead(Midpot));
  Serial.println("The range of the potentiometer is calibrated"); 
}

void loop() {
  wave();           //cycle through each of the hand positions, spending 10 seconds on each one
  delay(10000);
  relax();
  keygrab();
  delay(10000);
  relax();
  fist();
  delay(10000);
  relax();
}


void wave(){
  for (pos = 70; pos <= 110; pos += 1) { 
    moveLRwrist(pos);
    delay(15);                      
  }
  for (pos = 110; pos >= 70; pos -= 1) {  
    moveLRwrist(pos);
    delay(15);                       
  }
}

void keygrab(){         //works for holding objects like keys, credit cards, sd cards etc.
  moveIndex(180);
  delay(1000);          //1 second delay so you can place a key or card in position for the thumb to grasp
  moveThumb(130, -1);    //you might need to change the value of 130, see comment in instructable
  //don't forget to press the momentary button to stop the thumb contracting when it has a firm grip
}

void fist(){
  moveIndex(180);         //contract each of the fingers individually
  moveMiddle(180);
  movePinkyRing(180);
  moveThumb(130, -1);     //you might need to change the value of 130, see comment in instructable
  //don't forget to press the momentary button to stop the thumb contracting 
}

void relax(){
  moveIndex(90);         //contract each of the fingers individually
  moveMiddle(90);
  movePinkyRing(90);
  moveThumb(130, 1); 
  moveLRwrist(90);
  moveUDwrist(90);    
  //don't forget to press the momentary button to stop the thumb relaxing 
}


void moveThumb(int rotAngle, int contract){
  if (rotAngle<60 or rotAngle>140){               //you might need to change this range (see comment in instructable)
    Serial.println("Error, thumb rotation angle out of range"); 
  }
  else if (contract<-1 or contract>1 ){
    Serial.println("Error, thumb contraction out of range"); 
  }
  else{
    ThumbRot.write(pos);             
    delay(25);
    if (contract==-1){
        buttonState=digitalRead(ThumbButton);
        while (buttonState== LOW){                //keep rotating pulley until button is pushed
          ThumbContract.write(0);                 //contract the finger
          buttonState=digitalRead(ThumbButton);   //make sure you push the button otherwise the pulley will keep rotating until either the servo or the thumb breaks
          delay(25);
        }
    }
    else if(contract==1){
        buttonState=digitalRead(ThumbButton);
        while (buttonState== LOW){                //keep rotating pulley until button is pushed
          ThumbContract.write(0);                 //extend the finger
          buttonState=digitalRead(ThumbButton);   
          delay(25);
        }
    }
    //do nothing if contract=0
  }
}

void moveMiddle(int angle){
  if (angle<90 or angle>180){
    Serial.println("Error, middle finger angle out of range");
  }
  else{
    Mpot=analogRead(Midpot);
    angleMid=map(Mpot, MidExtd, MidCont, 90, 180);      //convert the raw analog value into a understandable range with the units of degrees
    if (angleMid<angle){                                //needs to contract finger to reach the angle
        while (angleMid<angle){
          Mid.write(180);                             //goes to the far extreme, since the potentiometer provides no meaningful reading
          Mpot=analogRead(Midpot);
          angleMid=map(Mpot, MidExtd, MidCont, 90, 180);
          delay(25);
        }
    }
    else if (angleMid>angle){                           //needs to relax finger to reach the angle
      while (angleMid>angle){
          Mid.write(0);                             
          Mpot=analogRead(Midpot);
          angleMid=map(Mpot, MidExtd, MidCont, 90, 180);
          delay(25);
        }
    }
  }
}

void moveIndex(int angle){
  if (angle<90 or angle>180){
    Serial.println("Error, index finger angle out of range");
  }
  else{
    Index.write(angle);
    delay(25);
  }
}

void movePinkyRing(int angle){
  if (angle<90 or angle>180){
    Serial.println("Error, pinky/ring finger angle out of range");
  }
  else{
    PinkyRing.write(angle);
    delay(25);
  }
}

void moveUDwrist(int angle){
  if (angle<70 or angle>110){   
    Serial.println("Error, angle out of range for wrist motion");
  }
  else{
    UDwrist.write(angle);
    delay(25);
  }
}

void moveLRwrist(int angle){
  if (angle<70 or angle>110){   
    Serial.println("Error, angle out of range for wrist motion");
  }
  else{
    LRwrist.write(angle);
    delay(25);
  }
}

