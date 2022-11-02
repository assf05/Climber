
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


	
}
