#include "HardwareSerial.h"
/* cpp code for Climber library
v0.1
using Default I2C pins : SCL = A5, SDA = A4 
by Ido Azran & Assf Saces
2022
*/
 #include "Arduino.h"
 #include "Climber.h"
 #include <Wire.h>
 #include <GY521.h> 
 #include <SoftwareSerial.h>
 

static const int en1 = 3; 
static const int en2 = 4; 
static const int enA = 2; // connected to l298n, left motor

static const int en3 = 5; 
static const int en4 = 6; 
static const int enB = 7; // connected to l298n, right motor 

int left_speed; 
int right_speed;

GY521 sensor(0x69); // connected to gyro, I2C Address 0x69
float yaw;

float manualENA_SPD = 0;
float manualENB_SPD = 0;  

 int YAW_MIN_ERROR = -3;
 int YAW_MAX_ERROR = 3;


Climber::Climber() {
  //this->speed = speed; //assign motors speed or - delay
}

void Climber::begin() {
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(enA, OUTPUT);
  
  pinMode(en3, OUTPUT);
  pinMode(en4, OUTPUT);
  pinMode(enB, OUTPUT);
  
  Serial.begin(9600);
  Wire.begin();
  delay(100);

}



void Climber::move(int left_speed, int right_speed) { //moves both motors with speed(pwm) 

  analogWrite(enA, left_speed); //moves left moter with left_speed(pwm)
  analogWrite(enB, right_speed);//moves left moter with right_speed(pwm)

  if(left_speed > 0){
	  digitalWrite(en1, HIGH);
	  digitalWrite(en2, LOW);
  } 
  else{
	  digitalWrite(en1, LOW);
	  digitalWrite(en1, HIGH);
  }
  
    if(right_speed > 0){
	  digitalWrite(en3, HIGH);
	  digitalWrite(en4, LOW);
  } 
  else{
	  digitalWrite(en3, LOW);
	  digitalWrite(en4, HIGH);
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

	if(let == "U"){ //Up

				 
			     digitalWrite(en1, HIGH);
	             digitalWrite(en2, LOW);
				 
	             digitalWrite(en3, HIGH);
	             digitalWrite(en4, LOW);
	}
	else if(let == "D"){ //Down

				 
	 			 digitalWrite(en1, LOW);
	             digitalWrite(en2, HIGH);
				 
	             digitalWrite(en3, LOW);
	             digitalWrite(en4, HIGH); 		
	}
	else if(let == "R"){ //Right

				 
			     digitalWrite(en1, HIGH);
	             digitalWrite(en2, LOW);
				 
	             digitalWrite(en3, HIGH);
	             digitalWrite(en4, LOW);	
	}
	else if(let == "L"){ //Left

				 
			     digitalWrite(en1, HIGH);
	             digitalWrite(en2, LOW);
				 
	             digitalWrite(en3, HIGH);
	             digitalWrite(en4, LOW);	
	}
 
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
		
  } 

void Climber::AutoMode(){ 
 begin();
 GyroYawCalibration();	 
  yaw = sensor.getYaw();
	
 if(yaw > YAW_MIN_ERROR && yaw < YAW_MAX_ERROR){ // robot in exceptable range, robot driving stright
  left_speed = 200; 
  right_speed = 200; 
  move(left_speed, right_speed);
} 

else if (yaw < YAW_MIN_ERROR) {  // robot to far left
  left_speed--; 
  right_speed = 200; 
  move(left_speed, right_speed);
} 

else {   // robot to far right
  left_speed = 200; 
  right_speed--; 
  move(left_speed, right_speed);
   }  
}






