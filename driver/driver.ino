#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

// define pins
int leftIRPin = A0;
int rightIRPin = A1;

int speed_ = 10;

char prevIRReading = 'l';

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

  leftMotor->run(RELEASE);
  rightMotor->run(RELEASE);
}

bool onTarget(int irReading) {
  Serial.println(irReading);
  return irReading > 725;
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
  int leftMotorSpeed = 0;
  int rightMotorSpeed = 0;
  switch(pos) {
    case 'L':
      leftMotorSpeed = 10;
      rightMotorSpeed = 2;
      break;
    case 'l':
      leftMotorSpeed = 7;
      rightMotorSpeed = 5;
      break;
    case 'O':
    case 'g':
      leftMotorSpeed = 6;
      rightMotorSpeed = 6;
      break;
    case 'r':
      leftMotorSpeed = 5;
      rightMotorSpeed = 7;
      break;
    case 'R':
      leftMotorSpeed = 2;
      rightMotorSpeed = 10;
      break;
    default:
      break;
  }
  leftMotorSpeed *= speed_;
  rightMotorSpeed *= speed_;
  
  leftMotor->setSpeed(leftSpeed);
  rightMotor->setSpeed(rightSpeed);
  
  return;
}

//void speedAngleCommands(int speed_, int angle) {
//  /* speed is a velocity and angle is a bearing from north */
//  
//  // convert speed and angle into two vectors
//  
//  
//  // assign motor speeds
//  uint8_t leftSpeed;
//  uint8_t rightSpeed;
//
//  leftMotor->setSpeed(leftSpeed);
//  rightMotor->setSpeed(rightSpeed);
//}

void loop() {
  // read IR data
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
  // driveMotors(pos);
  
  // wait
  delay(100);
}
