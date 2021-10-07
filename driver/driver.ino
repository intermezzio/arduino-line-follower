#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

// define pins
int leftIRPin = A0;
int rightIRPin = A1;

void setup() {
  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
}

bool onTarget(int irReading) {
  return false;
}

char processIRData(int leftIR, int rightIR) {
  bool leftDetect = onTarget(leftIR);
  bool rightDetect = onTarget(rightIR);
  if(!leftDetect && !rightDetect) {
    return 'o';
  } else if(rightDetect) {
    // correct by moving right
    return 'r';
  } else if(leftDetect) {
    // correct by moving left
    return 'l';
  } else {
    // good
    return 'g';
  }
}

void speedAngleCommands(int speed_, int angle) {
  /* speed is a velocity and angle is a bearing from north */
  
  // convert speed and angle into two vectors
  
  
  // assign motor speeds
  uint8_t leftSpeed;
  uint8_t rightSpeed;

  leftMotor->setSpeed(leftSpeed);
  rightMotor->setSpeed(rightSpeed);
}

void loop() {
  // read IR data
  int leftIR = analogRead(leftIRPin);
  int rightIR = analogRead(rightIRPin);
  
  // determine situation from IR data
  // eg left, right, center
  
  // PID control, convert situation
  // to speed/direction

  // output speed and direction

  // wait
  delay(10);
}
