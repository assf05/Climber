

/* /////               Climber Software       ///////////////////////
    An Climber Robot 

    v0.1.2b

By: Ido Azran And Assaf Sachs
2022
*/

#include "Climber.h" 
#include "SoftwareSerial.h"

Climber climber; //create Climber object 

//The boolean veriables that will send the robot to different modes based on when they are true

 bool isManual = false; 
 bool isAuto = false; 
 bool isUpdate = false;

 String let; //The letter that send the robot to different modes gets the letter from the app

void setup() {
  climber.begin(); 
  climber.GyroYawCalibration();
}

void loop() {   
if(Serial.available() > 0){	
let = Serial.readString();

if(let == "A" || let == "M" || let == "V"){
	
if(let == "A") //sends the robot to auto mode
isAuto = true;	
	
else if(let == "M") //sends the robot to manual mode
isManual = true;	 
	
else if(let == "V") //sends the robot to update mode
isUpdate = true;	
} 
	
if(let = "Z"){ //Exited from Mode
 isAuto = false; 
 isManual = false; 
 isUpdate = false;	
} 

if(isAuto) //auto mode
 climber.AutoMode();
	
if(isManual) //manual mode
 climber.BluetoothController(let); 
	
if(isUpdate) //update mode
  climber.BluetoothUpdateVariables(let);
 	
} 
}
