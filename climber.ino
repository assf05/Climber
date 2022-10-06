
/* /////               Climber Software       ///////////////////////
    An Climber Robot 

    v0.0.2b

By: Ido Azran And Assf Saces
2022
*/

#include "Climber.h"


Climber climber; //create Climber object 


int left_speed = 200; 
int right_speed = 200; 

final int YAW_MIN_ERROR = -3;
final int YAW_MAX_ERROR = 3;

float y;


void setup() {
  			
  climber.begin(); 
  climber.GyroYawCalibration();
  
}

void loop() {  

  y = climber.GetYaw();

  if(y > YAW_MIN_ERROR && y < YAW_MAX_ERROR){ // robot in exceptable range, robot driving stright
  left_speed = 200; 
  right_speed = 200; 
  climber.move(left_speed, right_speed);
} 

else if (y < YAW_MIN_ERROR) {  // robot to far left
  left_speed--; 
  right_speed = 200; 
  climber.move(left_speed, right_speed);
} 

else {   // robot to far right
  left_speed = 200; 
  right_speed--; 
  climber.move(left_speed, right_speed);
}
	
 climber.cli();
	
}
