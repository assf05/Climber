#include "HardwareSerial.h"
/* cpp code for Climber library
v0.0.2
using Default I2C pins : SCL = A5, SDA = A4 
by Ido Azran & Assf Saces
2022
*/
 #include "Arduino.h"
 #include "Climber.h"
 #include <Wire.h>
 #include <GY521.h> 
 #include <SoftwareSerial.h>
 

static const int en1 = 1; 
static const int en2 = 2; 
static const int enA = 5; // connected to l298n, left motor

static const int en3 = 3; 
static const int en4 = 4; 
static const int enB = 6; // connected to l298n, right motor

GY521 sensor(0x69); // connected to gyro, I2C Address 0x69
float yaw;

SoftwareSerial BTSerial(2, 3); // RX | TX 
char let;
float manualENA_SPD = 0;
float manualENB_SPD = 0; 
float enA = 6; 
float enB = 7;

Climber::Climber() {
  //this->speed = speed; //assign motors speed or - delay
}

void Climber::begin() {
  Serial.begin(115200);
  BTSerial.begin(115200);
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
  analogWrite(enA, left_speed); //moves left moter with left_speed(pwm)
  analogWrite(enB, right_speed);//moves left moter with right_speed(pwm)
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
 
void Climber::BluetoothController() {
	if(BTSerial.available()){
   	let = BTSerial.read();
 } 
	switch (let) { 
	  case U: // Stright
		 analogWrite(enA, 255); 
                 analogWrite(enB, 255); 
	   break;
			
	 case D: // Backwards
		 analogWrite(enA, -255); 
                 analogWrite(enB, -255);
	  break;
			
	 case R: // Right
		 analogWrite(enA, 180); 
                 analogWrite(enB, 120);
	  break;

	 case L: //Left
		 analogWrite(enA, 120); 
                 analogWrite(enB, 180);
	  break;
}
	
void Climber::BluetoothUpdateVariables() 
{
    // Gyro Setup & Calibration
     Serial.println("Starting Calibration");
     sensor.setAccelSensitivity(2);  // 8g
     sensor.setGyroSensitivity(1);   // 500 degrees/s
     sensor.aye = -0.002;
     sensor.gye = -6.436; 
	
	BTSerial.print(sensor.getYaw());
	
	if(BTSerial.available())
   	let = BTSerial.read();
 }     
	
	BTSerial.println("Gyro Angle = " + sensor.read());
	num = BTserial.read();
	
	if(num <= 252)
	   manualENA_SPD = num;
	
	else
	    manualENB_SPD = num - 504;		
	
	analogWrite(enA, manualENA_SPD);
	analogWrite(enB, manualENB_SPD);
	
	delay(100);	
  } 

void Climber::AutoMode
{
	analogWrite(enA, 255);
	analogWrite(enB, 255);
 }
