#include "HardwareSerial.h"
/* cpp code for Climber library
v0.0.1
using Default I2C pins : SCL = A5, SDA = A4 
by Ido Azran & Assf Saces
2022
*/
 #include "Arduino.h"
 #include "Climber.h"
 #include <Wire.h>
 #include <GY521.h> 

 
static const int enA = 5; // connected to l298n, left motor
static const int enB = 6; // connected to l298n, right motor
 GY521 sensor(0x69); // connected to gyro, I2C Address 0x69
float yaw;



Climber::Climber() {
  //this->speed = speed; //assign motors speed or - delay
}

void Climber::begin() {
  Serial.begin(115200);
  Wire.begin();
  delay(100);

  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }  

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
  digitalWrite(enA, left_speed); //moves left moter with left_speed(pwm)
  digitalWrite(enB, right_speed);//moves left moter with right_speed(pwm)
 }

 float Climber::GetYaw() {
  sensor.read();
  yaw = sensor.getYaw();
  Serial.println("Yaw Angle =  " + yaw);
  return yaw;
}

void Climber::GyroYawCalibration() {
  Serial.println("Starting Calibration");
  sensor.setAccelSensitivity(2);  // 8g
  sensor.setGyroSensitivity(1);   // 500 degrees/s
  sensor.aye = -0.002;
  sensor.gye = -6.436;
}
 
 
