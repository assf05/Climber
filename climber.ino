

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

 char BTlet;

void setup() {
  climber.begin(); 
  climber.GyroYawCalibration();
}

void loop() {   
BTlet = climber.getCharBT(); 

if(BTlet == 'A' || BTlet == 'M' || BTlet == 'V'){
switch(BTlet) {
 case 'A': //Auto Mode 
	isAuto = true;
   break;
 case 'M': //Manual Mode 
	isManual = true;
   break;
 case 'V': //UpdateVariables Mode 
	isUpdate = true;
   break; }
} 
	
if(BTlet = 'Z'){ //Exited from Mode
 isAuto = false; 
 isManual = false; 
 isUpdate = false;	
} 

if(isAuto)
 climber.AutoMode();
	
if(isManual)
 climber.BluetoothController(); 
	
if(isUpdate)
  climber.BluetoothUpdateVariables();
 	
}
