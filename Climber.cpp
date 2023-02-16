#include "HardwareSerial.h"
/* cpp code for Climber library
v0.1
using Default I2C pins : SCL = A5, SDA = A4 
by Ido Azran & Assaf Sachs
2022
motors that are connected to OUT1 & OUT2 are on the right side of the robot. motors that are connected to OUT3 & OUT4 are on the left side of the robot.
*/
 #include "Arduino.h"
 #include "Climber.h"
 #include <Wire.h>
 #include <GY521.h> 
 #include <SoftwareSerial.h>
 #include "HCPCA9685.h"

 
//Motor Driver 1
static const int MD1en1 = 22; 
static const int MD1en2 = 23; 
static const int MD1en3 = 24; 
static const int MD1en4 = 25; 

//Motor Driver 2
static const int MD2en1 = 26; 
static const int MD2en2 = 27; 
static const int MD2en3 = 28; 
static const int MD2en4 = 29; 

//Motor Driver 3
static const int MD3en1 = 30; 
static const int MD3en2 = 31; 
static const int MD3en3 = 32; 
static const int MD3en4 = 33; 

int[in1Pins = {MD1en1, MD2en1, MD3en1};
int[]in2Pins = {MD1en2, MD2en2, MD3en2};
int[]in3Pins = {MD1en3, MD2en3, MD3en3};
int[]in4Pins = {MD1en4, MD2en4, MD3en4};


int left_speed; 
int right_speed;

GY521 sensor(0x69); // connected to gyro, I2C Address 0x69
float yaw;

float manualENA_SPD = 0;
float manualENB_SPD = 0;  

 int YAW_MIN_ERROR = -3;
 int YAW_MAX_ERROR = 3; 

HCPCA9685 pwmDriver(0x40);
    
int i;



Climber::Climber() {
  //this->speed = speed; //assign motors speed or - delay
}

void Climber::begin() {
	//Motor Driver 1
  pinMode(MD1en1, OUTPUT);
  pinMode(MD1en2, OUTPUT);
  pinMode(MD1en3, OUTPUT);
  pinMode(MD1en4, OUTPUT);
	//Motor Driver 2	 
  pinMode(MD2en1, OUTPUT);
  pinMode(MD2en2, OUTPUT);
  pinMode(MD2en3, OUTPUT);
  pinMode(MD2en4, OUTPUT);
	//Motor Driver 3
  pinMode(MD3en1, OUTPUT);
  pinMode(ND3en2, OUTPUT);
  pinMode(MD3en3, OUTPUT);
  pinMode(MD3en4, OUTPUT);
	
  pwmDriver.Init();
  pwmDriver.Sleep(false);
  
  Serial.begin(9600);
  Wire.begin();
  delay(100);

}



void Climber::moveUp(HCPCA9685 pwmDriver) { //moves robot foward with speed(pwm) 
	
	for(int i = 0; i < 6; i++)
	pwmDriver(i,0,4095);	
	
		for(i = 0; j < 3; j++){
			digitalWrite(in1Pins[j], HIGH);
			digitalWrite(in2Pins[j], LOW);
			digitalWrite(in3Pins[j], HIGH);
			digitalWrite(in4Pins[j], LOW);
  	}
 }

void Climber::moveDown(HCPCA9685 pwmDriver) { //moves robot backwards with speed(pwm) 
	
	for( i = 0; i < 6; i++)
	pwmDriver(i,0,4095);	
	
		for(i= 0; i < 3; i++){
			digitalWrite(in1Pins[j], LOW);
			digitalWrite(in2Pins[j], HIGH);
			digitalWrite(in3Pins[j], LOW);
			digitalWrite(in4Pins[j], HIGH);
  	}
 }
 
  void Climber::moveRight(HCPCA9685 pwmDriver) { //moves robot right with speed(pwm) 
	
	for( i = 0; i < 6; i++)
	pwmDriver(i,0,4095);	
	
		for(i= 0; i < 3; i++){
			digitalWrite(in1Pins[j], LOW);
			digitalWrite(in2Pins[j], HIGH);
			digitalWrite(in3Pins[j], HIGH);
			digitalWrite(in4Pins[j], LOW);
  	}
 }

void Climber::moveLeft(HCPCA9685 pwmDriver) { //moves robot left with speed(pwm) 
	
	for( i = 0; i < 6; i++)
	pwmDriver(i,0,4095);	
	
		for(i= 0; i < 3; i++){
			digitalWrite(in1Pins[j], HIGH);
			digitalWrite(in2Pins[j], LOW);
			digitalWrite(in3Pins[j], LOW);
			digitalWrite(in4Pins[j], HIGH);
  	}
 }
    

 float Climber::GetYaw() {
  sensor.read();
  yaw = sensor.getYaw();
  Serial.println(yaw);
  return yaw;
}

void Climber::GyroYawCalibration() {
  sensor.setAccelSensitivity(2);  // 8g
  sensor.setGyroSensitivity(1);   // 500 degrees/s
  sensor.aye = -0.002;
  sensor.gye = -6.436;
}
 
void Climber::BluetoothController(String let) { 

	if(let == "U") //Up		 
		moveUp(pwmDriver);
	else if(let == "D") //Down
		moveDown(pwmDriver);
	else if(let == "R") //Right
		moveRight(pwmDriver);
	else if(let == "L") //Left
		moveLeft(pwmDriver);
 
	/* switch (let) { 
	  case "U": // Stright
	             analogWrite(enA, 255); 
                 analogWrite(enB, 255); 
				 
			     digitalWrite(en1, HIGH);
	             digitalWrite(en2, LOW);
				 
	             digitalWrite(en3, HIGH);
	             digitalWrite(en4, LOW);
				 
		         
	   break;
			
	 case "D": // Backwards
	             analogWrite(enA, -255); 
                 analogWrite(enB, -255);
				 
	 			 digitalWrite(en1, LOW);
	             digitalWrite(en2, HIGH);
				 
	             digitalWrite(en3, LOW);
	             digitalWrite(en4, HIGH); 
				 

	  break;
			
	 case "R": // Right
			     analogWrite(enA, 180); 
                 analogWrite(enB, 120);
				 
			     digitalWrite(en1, HIGH);
	             digitalWrite(en2, LOW);
				 
	             digitalWrite(en3, HIGH);
	             digitalWrite(en4, LOW);	 

	  break;

	 case "L": //Left
	 		     analogWrite(enA, 120); 
                 analogWrite(enB, 180);
				 
			     digitalWrite(en1, HIGH);
	             digitalWrite(en2, LOW);
				 
	             digitalWrite(en3, HIGH);
	             digitalWrite(en4, LOW);	 

	  break;
}
*/
}
void Climber::BluetoothUpdateVariables(String let){
/*
    // Gyro Calibration & Get info
    	GyroYawCalibration(); 
     	GetYaw();
	
	Serial.print(sensor.getYaw());
	  
	
	Serial.print(sensor.read());
    int num = let.toInt();
	
	if(num <= 252)
	   manualENA_SPD = num;
	
	else
	    manualENB_SPD = num - 504;		
	
	analogWrite(enA, manualENA_SPD);
		if(num < 0) {
	 	digitalWrite(en1, LOW);
	    digitalWrite(en2, HIGH);	
	}  
	else if(num > 0 && num >= 252){
	 	digitalWrite(en1, HIGH);
	    digitalWrite(en2, LOW);			
	}
	analogWrite(enB, manualENB_SPD); 
        if(num > 252 && num < 504){
	 	digitalWrite(en3, LOW);
	    digitalWrite(en4, HIGH);		 
	 } 
	 else if(num > 504){
	 digitalWrite(en3, HIGH);
	 digitalWrite(en4, LOW);		 
	 }
*/		
  } 

void Climber::AutoMode(){ 
 begin();
 GyroYawCalibration();	 
  yaw = sensor.getYaw();
	
 if(yaw > YAW_MIN_ERROR && yaw < YAW_MAX_ERROR){ // robot in exceptable range, robot driving stright
  moveUp(pwmDriver);
} 

else if (yaw < YAW_MIN_ERROR) {  // robot to far left
  moveRight(pwmDriver);
} 

else {   // robot to far right
  moveRight(pwmDriver);
   }  
}






