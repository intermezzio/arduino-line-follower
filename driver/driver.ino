#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);

// define pins
int leftIRPin = A0;
int rightIRPin = A1;

int speed_ = 4;

char prevIRReading = 'g';

void setup() {
  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);

  Serial.begin(9600);
  
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
      Serial.println("Could not find Motor Shield. Check wiring.");
    }
  }
  Serial.println("Motor Shield found.");
  
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}

bool onTarget(int irReading) {
  Serial.println(irReading);
  return irReading > 550;
}

char processIRData(int leftIR, int rightIR) {
  bool leftDetect = onTarget(leftIR);
  bool rightDetect = onTarget(rightIR);
  if(!leftDetect && !rightDetect) {
    if(prevIRReading == 'l' || prevIRReading == 'L') {
      return 'L';
    } else if(prevIRReading == 'r' || prevIRReading == 'R') {
      return 'R';
    }
    return 'O';
  } else if(rightDetect && !leftDetect) {
    // correct by moving right
    return 'r';
  } else if(leftDetect && !rightDetect) {
    // correct by moving left
    return 'l';
  } else {
    // good
    return 'g';
  }
}

void driveMotors(char pos) {
//  Serial.println("Driving motors");
  int leftMotorSpeed = 0;
  int rightMotorSpeed = 0;
  switch(pos) {
    case 'O':
    case 'L':
      leftMotorSpeed = 4;
      rightMotorSpeed = 0;
      break;
    case 'l':
      leftMotorSpeed = 4;
      rightMotorSpeed = 0;
      break;
    case 'g':
      leftMotorSpeed = 7;
      rightMotorSpeed = 7;
      break;
    case 'r':
      leftMotorSpeed = 0;
      rightMotorSpeed = 4;
      break;
    case 'R':
      leftMotorSpeed = 0;
      rightMotorSpeed = 4;
      break;
    default:
      break;
  }
  leftMotorSpeed *= speed_;
  rightMotorSpeed *= speed_;

  Serial.print("left speed: ");
  Serial.println(leftMotorSpeed);
  Serial.print("right speed: ");
  Serial.println(rightMotorSpeed);
  
  leftMotor->setSpeed(leftMotorSpeed);
  rightMotor->setSpeed(rightMotorSpeed);
  
  return;
}

void getInput() {
  if(Serial.available() == 0) {
    return;
  }
  int newSpeed = Serial.parseInt();
  if(newSpeed < 0 || newSpeed > 32) {
    // invalid data
    Serial.print("Invalid speed ");
    Serial.println(newSpeed);
    return;
  }
  if(newSpeed == 0) {
    Serial.println("Terminating code");
    // end code by trapping in a while loop
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
    while(true) {}
  }
  speed_ = newSpeed;
  return;
}

void loop() {
  // read IR data
  Serial.println("Getting IR readings:");
  int leftIR = analogRead(leftIRPin);
  int rightIR = analogRead(rightIRPin);
  
  // determine situation from IR data
  // eg left, right, center
  char pos = processIRData(leftIR, rightIR);
  Serial.println(pos);
  
  // PID control, convert situation
  // to speed/direction
  // void
  
  // output speed and direction
  driveMotors(pos);

  // read Serial input for speed change
  getInput();
  
  // wait
  delay(10);
}
