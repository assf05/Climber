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
 #include <Adafruit_PWMServoDriver.h>
 #include <L298NX2.h>
 
//Motor Driver 1, Front Motors
static const int MD1en1 = 8; 
static const int MD1en2 = 9; 
static const int MD1en3 = 10; 
static const int MD1en4 = 11;  
static const int MD1enA = 2;  
static const int MD1enB = 3;  

//Motor Driver 2, Middle Motors
static const int MD2en1 = 22; 
static const int MD2en2 = 23; 
static const int MD2en3 = 24; 
static const int MD2en4 = 25; 
static const int MD2enA = 4;  
static const int MD2enB = 5; 

//Motor Driver 3, Back Motors
static const int MD3en1 = 26; 
static const int MD3en2 = 27; 
static const int MD3en3 = 28; 
static const int MD3en4 = 29; 
static const int MD3enA = 6;  
static const int MD3enB = 7; 

L298NX2 MD1(MD1enA, MD1en1, MD1en2, MD1en3, MD1en4, MD1enB);
L298NX2 MD2(MD2enA, MD2en1, MD2en2, MD2en3, MD2en4, MD2enB);
L298NX2 MD3(MD3enA, MD3en1, MD3en2, MD3en3, MD3en4, MD3enB);

int left_speed; 
int right_speed;

GY521 sensor(0x69); // connected to gyro, I2C Address 0x69
float yaw;

float manualENA_SPD = 0;
float manualENB_SPD = 0;  

 int YAW_MIN_ERROR = -3;
 int YAW_MAX_ERROR = 3; 

Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);//object to represent PCA9685 at default I2C address  (0x40, more extensions up to 0x60)
    
int i;



Climber::Climber() {
  //this->speed = speed; //assign motors speed or - delay
}

void Climber::begin() {

	

  
  Serial.begin(9600);
  MD1.setSpeed(80); 
  MD2.setSpeed(80); 
  MD3.setSpeed(80); 
  Wire.begin();
  delay(100);
}



void Climber::moveUp() { //moves robot foward with speed(pwm) 
	MD1.forward();
	MD2.forward(); 
	MD3.forward();
 } 
    


void Climber::moveDown() { //moves robot backwards with speed(pwm) 
	MD1.backward();
	MD2.backward(); 
	MD3.backward();
  	}
 }
 
  void Climber::moveRight() { //moves robot right with speed(pwm) 
	
	for( i = 0; i < 6; i++)
		SetMotorPWM(i,255);	
	
		for(i= 0; i < 3; i++){
			digitalWrite(in1Pins[j], LOW);
			digitalWrite(in2Pins[j], HIGH);
			digitalWrite(in3Pins[j], HIGH);
			digitalWrite(in4Pins[j], LOW);
  	}
 }

void Climber::moveLeft() { //moves robot left with speed(pwm) 
	
	for( i = 0; i < 6; i++)
		SetMotorPWM(i,255);	
	
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
		moveUp();
	else if(let == "D") //Down
		moveDown();
	else if(let == "R") //Right
		moveRight();
	else if(let == "L") //Left
		moveLeft();
 
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
  moveUp();
} 

else if (yaw < YAW_MIN_ERROR) {  // robot to far left
  moveRight();
} 

else {   // robot to far right
  moveRight();
   }   
	
}






