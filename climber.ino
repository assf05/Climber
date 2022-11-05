

/* /////               Climber Software       ///////////////////////
    An Climber Robot 

    v0.1.2b

By: Ido Azran And Assf Saces
2022
*/

#include "Climber.h" 
#include "SoftwareSerial.h"

Climber climber; //create Climber object 

 bool isManual = false; 
 bool isAuto = false; 
 bool isUpdate = false;

 String BTlet;

void setup() {
  climber.begin(); 
  climber.GyroYawCalibration();
}

void loop() {   
if(Serial.available() > 0){	
let = Serial.readString();

if(let == "A" || let == "M" || let == "V"){
	
if(let == "A")
isAuto = true;	
	
if(let == "M")
isManual = true;	 
	
if(let == "V")
isUpdate = true;	
} 
	
if(let = "Z"){ //Exited from Mode
 isAuto = false; 
 isManual = false; 
 isUpdate = false;	
} 

if(isAuto)
 climber.AutoMode();
	
if(isManual)
 climber.BluetoothController(let); 
	
if(isUpdate)
  climber.BluetoothUpdateVariables(let);
 	
} 
}
