/* cpp code for Climber library
v1.0.0
using Default I2C pins : SCL, SDA = A5, A4 
by ido azran
2022
*/
 #include "Arduino.h"
 #include "Climber.h"
 #include <Wire.h>
 #include <GY521.h> 

 
static const int enA = 5; // connected to l298n, left motor
static const int enB = 6; // connected to l298n, right motor
GY521 sensor(0x69); // connected to gyro, I2C Address 0x69
float y;


Climber::Climber() {
  //this->speed = speed; //assign motors speed or - delay
}

void Climber::begin() {
  Serial.begin(115200);       
  Serial.println("Climber Initiated");
  pinMode(enA,OUTPUT); 
  pinMode(enB,OUTPUT);
}


void Climber::move(int left_speed, int right_speed) { //moves both motors with speed(pwm)
  Serial.println("move activated");
  Serial.print("Right Speed =");
  Serial.print(right_speed);
  Serial.print("  |  Left Speed =");
  Serial.println(left_speed);
 }


void Climber::GetYaw() {
  sensor.read();
  y = sensor.getYaw();
}


 
