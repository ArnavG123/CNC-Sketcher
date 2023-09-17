//Includes the Arduino Stepper Library
#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int limitPin = 3;
int readPin = 2;
int xPos = 0;

void setup() {
    pinMode(readPin, INPUT_PULLUP);
    pinMode(readPin, INPUT);
    Serial.begin(9600);
    myStepper.setSpeed(17);

}

void loop() {
  if (digitalRead(readPin)==1){
    myStepper.step(2048);
    yPos++;

  }
  if (digitalRead(limitPin)==0){
    myStepper.step(-1);
    xPos=0;

  }
  else{
    	myStepper.step(stepsPerRevolution);
      xPos+=1;
  }


  Serial.println(yPos);
}
