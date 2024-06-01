#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

String voice;
int x = 0;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Define servo parameters
#define SERVO_MIN_PULSE 150  // Minimum pulse width (in ticks)
#define SERVO_MAX_PULSE 600  // Maximum pulse width (in ticks)
#define SERVO_MIN_DEG 0      // Minimum servo angle (degrees)
#define SERVO_MAX_DEG 180    // Maximum servo angle (degrees)

void setServoPosition(uint8_t servoNum, uint16_t degrees) {
  // Convert degrees to PWM pulse width
  uint16_t pulseWidth = map(degrees, SERVO_MIN_DEG, SERVO_MAX_DEG, SERVO_MIN_PULSE, SERVO_MAX_PULSE);
  pwm.setPWM(servoNum, 0, pulseWidth);
}



void sleep() {
  setServoPosition(0,0);
  setServoPosition(7,60);
  setServoPosition(1,180);
  setServoPosition(2,0);
  x = 0;
}

void wakeup() {
  setServoPosition(0,0);
  setServoPosition(7,30);
  setServoPosition(1,130);
  setServoPosition(2,150);
  x=0;
}
void left(){
  if(x<=0)
  {
    setServoPosition(0,0);
  }
  else if (0<x<180)
  {
    x=x-30;
    setServoPosition(0,x);
  }

}
void greet() {
  //setServoPosition(0,x);
  //setServoPosition(7,30);
  setServoPosition(1,100);
  delay(1000);
  setServoPosition(1,130);
  delay(1000);
  setServoPosition(2,0);
  delay(100);
  setServoPosition(2,150);
  ;
}

void right(){
  if(x>=180)
  {setServoPosition(0,180);}
  else if (0<x<180)
  {
    x=x+30;
    setServoPosition(0,x);
  }

}

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(50);
}

void loop() {
  if (Serial.available() > 0) {
    voice = Serial.readStringUntil('#'); // Read input until '#' is encountered
    executeCommand(voice);
  }
}

void executeCommand(String command) {
  Serial.println("Received command: " + command);
  
  if (command.equals("sleep")) {
    sleep();
  } 
  else if (command.equals("wake up")) {
    wakeup();
  }
  else if (command.equals("right")) {
    right();
  }
  else if (command.equals("left")) {
    left();
  }
  else if (command.equals("greet")) {
    greet();
  }
}
