
 //Original source: Arduino IDE
// Arduino Project: Controlling the servo position
// This code is used with a video tutorial for Robojax.com
// Published on April 24, 2017 from Aajx, ON, Canada.
// Written/Edited by Ahmad Shamshiri
// Watch the video on youTube https://youtu.be/kZ9b31gVemc
// Controlling a servo position using a potentiometer (variable resistor)
//

//Board Wiring   
//Right(Organge) -->> PIN 3(only PINs with ~ sign, pulsating ..??) 
//Center (RED)  --->> 5V    +ve? 
//Left(greyish) -- > GRND  -ve? 

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(15);  // attaches the servo on pin 15 (pulsating ?? 3,9 in Arduino ) to the servo object
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
}
