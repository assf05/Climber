
/* /////               Climber Software       ///////////////////////
    An Climber Robot 

    v0.0.2b

By: Ido Azran And Assf Saces
2022
*/

#include "Climber.h" 
#include "HardwareSerial.h"

Climber climber; //create Climber object 

 int YAW_MIN_ERROR = -3;
 int YAW_MAX_ERROR = 3;  
 
 bool isManual = false; 
 bool isAuto = false; 
 bool isUpdate = false;

SoftwareSerial BTSerial(2, 3); // RX | TX 

void setup() {
  climber.begin(); 
  climber.GyroYawCalibration();
}

void loop() {   
let = BTSerial.read(); 

if(let = 'A' || let = 'M' || let = 'V'){
switch(let) 
 case A: //Auto Mode 
	isAuto = true;
   break;
 case M: //Manual Mode 
	isManual = true;
   break;
 case V: //UpdateVariables Mode 
	isUpdate = true;
   break; 
} 
	
if(let = 'Z'){ //Exited from Mode
 isAuto = false; 
 isManual = false; 
 isUpdate = false;	
} 

if(isAuto)
 Climber.AutoMode();
	
if(isManual)
 Climber.BluetoothController(); 
	
if(isUpdate){
  Climber.BluetoothUpdateVariables();
 	
}
