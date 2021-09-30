// define pins
int leftIRPin = A0;
int rightIRPin = A1;

int leftMotorPin = 9;
int rightMotorPin = 10;

void setup() {
  pinMode(leftIRPin, INPUT);
  pinMode(rightIRPin, INPUT);

  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
}

void speedAngleCommands(int speed, int angle) {
  // convert speed and angle into two vectors

  // assign motor speeds
  
}

void loop() {
  // read IR data

  // determine situation from IR data
  // eg left, right, center

  // PID control, convert situation
  // to speed/direction

  // output speed and direction

  // wait
  delay(10);
}
