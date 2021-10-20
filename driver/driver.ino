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
const int leftIRPin = A0;
const int rightIRPin = A1;

int speed_ = 6;

const int LEFT_THRESHOLD = 725;
const int RIGHT_THRESHOLD = 400;

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

bool onTarget(int irReading, int THRESHOLD) {
  Serial.print(irReading);
  Serial.print(",");
  return irReading > THRESHOLD;
}

char processIRData(int leftIR, int rightIR) {
  bool leftDetect = onTarget(leftIR, LEFT_THRESHOLD);
  bool rightDetect = onTarget(rightIR, RIGHT_THRESHOLD);
  if(!leftDetect && !rightDetect) {
    return 'g';
  } else if(rightDetect && !leftDetect) {
    // correct by moving right
    return 'l';
  } else if(leftDetect && !rightDetect) {
    // correct by moving left
    return 'r';
  } else {
    // should not reach this state
    // both see the tape
    return 'x';
  }
}

void driveMotors(char pos) {
//  Serial.println("Driving motors");
  int leftMotorDirection = FORWARD;
  int rightMotorDirection = FORWARD;
  
  int leftMotorSpeed = 0;
  int rightMotorSpeed = 0;
  switch(pos) {
    case 'l':
      leftMotorSpeed = 4;
      rightMotorSpeed = -4;
      break;
    case 'x':
    case 'g':
      leftMotorSpeed = 4;
      rightMotorSpeed = 4;
      break;
    case 'r':
      leftMotorSpeed = -4;
      rightMotorSpeed = 4;
      break;
    default:
      break;
  }
  leftMotorSpeed *= speed_;
  rightMotorSpeed *= speed_;

//  Serial.print("left speed: ");
  Serial.print(leftMotorSpeed);
  Serial.print(",");
//  Serial.print("right speed: ");
  Serial.println(rightMotorSpeed);

  if(leftMotorSpeed < 0) {
    leftMotorSpeed = -leftMotorSpeed;
    leftMotorDirection = BACKWARD;
  }
  if(rightMotorSpeed < 0) {
    rightMotorSpeed = -rightMotorSpeed;
    rightMotorDirection = BACKWARD;
  }

  leftMotor->run(leftMotorDirection);
  rightMotor->run(rightMotorDirection);
  
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
  int leftIR = analogRead(leftIRPin);
  int rightIR = analogRead(rightIRPin);
  
  // determine situation from IR data
  // eg left, right, center
  char pos = processIRData(leftIR, rightIR);
  Serial.print(pos);
  Serial.print(",");
  
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
