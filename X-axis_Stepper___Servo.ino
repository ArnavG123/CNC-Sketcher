#include <Stepper.h>
#include <Servo.h>
#include <Wire.h>
// Defines the number of steps per rotation
const int stepsPerRevolution = 2048;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);
int limitPin = 3;
int xPos = 0;
int cols = 18;
int rows = 3;
int px[][18] = {{0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,1,0}, {1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1}, {0,0,1,1,1,0,0,0,1,1,1,0,0,0,1,1,1,0}};
bool penout = false;
Servo myservo;


void setup() {
    pinMode(limitPin, INPUT_PULLUP);
    pinMode(2, OUTPUT);
    myservo.attach(6);
    Serial.begin(9600);
    myStepper.setSpeed(10);
    if (px[0][0]=1){
      myservo.write(160);
      delay(100);
      myservo.write(0);
      penout=true;
    }
    
    Wire.begin();
}

void loop() {
  for (int r = 0; r < rows; r++){
    for (int x=0; x < cols; x++){             //x < (sizeof(px)/sizeof(px[0]))
      if (px[r][x]== 0 && penout == true){
        // penClick();
        myservo.write(0);
        penout = false;
      } 
      else if (px[r][x]== 1 && penout == false){
        // penClick();
        myservo.write(160);
        delay(100);
        penout = true;
      }
      
      myStepper.step(-20);
      delay(100);
      xPos += 1;
    }
    myservo.write(0);
    myStepper.step((cols+1)*25);
    delay(cols*100);
    xPos = 0;
    // myStepper.step(2048);
    Serial.println("Row Complete");
    
    Wire.beginTransmission(9); // transmit to device #9
    Wire.write(1);              // sends
    Wire.endTransmission();    // stop transmitting
    
    delay(500);
  }
  
  Serial.println("Array Complete");
//  digitalWrite(2, HIGH);
//  delay(500);
//  digitalWrite(2, LOW);
//  delay(500);
  
  if (digitalRead(limitPin) == 0){
    myStepper.step(1);
    xPos=0;
  }
}








void penClick(){
  myservo.write(90);
  delay(100);
  myservo.write(0);
}
