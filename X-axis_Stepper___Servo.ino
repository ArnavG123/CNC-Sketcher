#include <Stepper.h>
#include <Servo.h>
#include <Wire.h>
// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int readPin = 3;
int xPos = 0;
int px[] = {1,0,0,0};
bool penout = false;
Servo myservo;
 

void setup() {
    pinMode(readPin, INPUT);
    pinMode(2, OUTPUT);
    myservo.attach(6);
    Serial.begin(9600);
    myStepper.setSpeed(17);
    myservo.write(90);
    delay(100);
    myservo.write(0);
    penout=true;

    Wire.begin();
}

void loop() {
  for (int x=0; x<(sizeof(px)/sizeof(px[0])); x++){
    if (px[x]==0 && penout == true){
      penClick();
      penout = false;
    } 
    else if (px[x]==1 && penout == false){
      penClick();
      penout = true;
    }
    
    myStepper.step(2048);
  }
  
  Serial.println("Array Complete");
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);

  Wire.beginTransmission(9); // transmit to device #9
  Wire.write(1);              // sends
  Wire.endTransmission();    // stop transmitting
  delay(5000);
  
  if (digitalRead(readPin)==0){
    myStepper.step(-1);
    xPos=0;
  }

}

void penClick(){
  myservo.write(90);
  delay(100);
  myservo.write(0);
}
