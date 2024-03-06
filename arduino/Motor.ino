#include <PS4Controller.h> // Library for PS4 controller
#include <Wire.h> // Library for I2C communication
#include <Adafruit_MotorShield.h> // Library for Adafruit Motor Shield
 
// Create an instance of the Adafruit Motor Shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
 
// Connect the motors to the motor shield
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
 
// Create an instance of the PS4 controller
PS4Controller ps4;
 
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
 
  // Initialize motor shield
  AFMS.begin();
 
  // Set motor speed to 0 initially
  motor1->setSpeed(0);
  motor2->setSpeed(0);
 
  // Initialize PS4 controller
  if (!ps4.begin("Wireless Controller")) {
    Serial.println("Error: Unable to find PS4 controller.");
    while (1);
  }
  Serial.println("PS4 controller connected.");
}
 
void loop() {
  // Update PS4 controller data
  ps4.read();
 
  // Control motors based on PS4 controller input
  int leftStickY = ps4.leftStickY();
  int rightStickY = ps4.rightStickY();
 
  // Map controller input to motor speed (-255 to 255)
  int motorSpeed1 = map(leftStickY, -128, 127, -255, 255);
  int motorSpeed2 = map(rightStickY, -128, 127, -255, 255);
 
  // Set motor speed
  motor1->setSpeed(abs(motorSpeed1));
  motor2->setSpeed(abs(motorSpeed2));
 
  // Set motor direction based on controller input
  if (motorSpeed1 > 0) {
    motor1->run(FORWARD);
  } else {
    motor1->run(BACKWARD);
  }
  if (motorSpeed2 > 0) {
    motor2->run(FORWARD);
  } else {
    motor2->run(BACKWARD);
  }
 
  // Print motor speeds for debugging
  Serial.print("Motor 1 Speed: ");
  Serial.println(motorSpeed1);
  Serial.print("Motor 2 Speed: ");
  Serial.println(motorSpeed2);
 
  // Delay to avoid overwhelming the serial monitor
  delay(100);
}