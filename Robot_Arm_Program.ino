#include <Servo.h>

// Initialize joystick values
int base_axis;
int lin_axis;
const int HI_END = 600;
const int LO_END = 350;

// Create servos
Servo servo_base;
Servo servo_lin;
Servo servo_claw;

// Initialize button variables
int pin = 13;
int button_down;
bool lock = false;

// Claw tracking
const int CLAW_TIME = 85;

void setup() {
  // Start debug log
  Serial.begin(9600);

  // Attach servos
  servo_base.attach(10);
  servo_lin.attach(9);
  servo_claw.attach(6);

  // Initialize button control
  pinMode(pin, INPUT);
  digitalWrite(pin, HIGH);
}

void loop() {
  // Get joystick values
  base_axis = analogRead(0);
  lin_axis = analogRead(1);

  // Get button pressed
  button_down = digitalRead(pin);

  // Check inputs and execute movements
  if (base_axis > HI_END) {
    servo_base.write(63);
    delay(15);
    Serial.println(base_axis);
  }
  else if (base_axis < LO_END) {
    servo_base.write(127);
    delay(15);
    Serial.println(base_axis);
  }
  else if (lin_axis > HI_END) {
    servo_lin.write(63);
    delay(15);
    Serial.println(base_axis);
  }
  else if (lin_axis < LO_END) {
    servo_lin.write(127);
    delay(15);
    Serial.println(base_axis);
  }
  else {
    servo_base.write(0);
    delay(15);
    servo_lin.write(0);
    delay(15);
  }

  // Check button condition
  if (button_down == 0 && !lock) {
    servo_claw.write(63);
    delay(CLAW_TIME);
    servo_claw.write(0);
    delay(15);
    lock = true;
  }
  else if (button_down == 1 && lock) {
    servo_claw.write(127);
    delay(CLAW_TIME + 20);
    servo_claw.write(0);
    delay(15);
    lock = false;
  }
}
