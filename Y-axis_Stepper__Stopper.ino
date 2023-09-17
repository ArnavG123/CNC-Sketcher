#include <Stepper.h>
#include <Wire.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int limitPin = 3;
int yPos = 0;
int xData = 0;

void receiveEvent(int bytes){
  xData = Wire.read();
  Serial.print("data recieved: ");
  Serial.println(xData);
}

void setup() {
    pinMode(limitPin, INPUT_PULLUP);
    Serial.begin(9600);
    myStepper.setSpeed(17);

    Wire.begin(9);
    // Attach a function to trigger when something is received.
    Wire.onReceive(receiveEvent);
}

void loop() {
  if (xData == 1){
//    Serial.println("1 hi");
    myStepper.step(-25);
    yPos++;
    xData = 0;
//    Serial.println("1 bye");
  }
  
  if (digitalRead(limitPin) == 0){
    myStepper.step(-1);
    yPos=0;
  }

//  Serial.println(yPos);
}
