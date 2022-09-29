
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


 //This is the CLI Functionality
 // You can add cases with new functionalities 
 // CLI - Messages from Terminal
  while (Serial.available() > 0) { 
   char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;
   char inByte = Serial.read();   //Read the next available byte in the serial receive buffer
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
     {
     message[message_pos] = inByte;  //Add the incoming byte to our message
     message_pos++;
     }
     //Full message received...
     else
     {
      message[message_pos] = '\0';     //Add null character to string
      Serial.println(message);     //echo the message to terminal
        
      int command[4];
      int argindex = 0;
      char cmd;
      char delim[] = " ";
	     char tmpmsg[MAX_MESSAGE_LENGTH];
       strcpy(tmpmsg,message);
       message_pos = 0;
       message[message_pos] = '\0';     //Add null character to string

        char *ptr = strtok(tmpmsg, delim);
	      while(ptr != NULL)
	       {
		      //Serial.printf("'%s'\n", ptr);
          if (argindex == 0) {
            cmd = ptr[0];
          }
          command[argindex] = atoi(ptr);   
          //Serial.println(command[argindex]);
          argindex++;  
		      ptr = strtok(NULL, delim);
	       } 

      switch (cmd) {
       case 'h': //Set port to HIGH
        pinMode(command[1],OUTPUT);
        digitalWrite(command[1],HIGH);
        Serial.println("Pin SET");   
        delay(1000);
        break;
       case 'l': // Set port to LOW
        pinMode(command[1],OUTPUT);
        digitalWrite(command[1],LOW);
        Serial.println("Pin RESET");   
        delay(1000);
        break;
       
       case 'a': // analog Write to pwm ports
        pinMode(command[1],OUTPUT);
        analogWrite(command[1],command[2]);
        Serial.println("writing analog value");   
        delay(1000);
        break;

       case 'r': // digital read
        pinMode(command[1],INPUT);
        Serial.print("Pin Value ="); 
        Serial.println(digitalRead(command[1]));   
        delay(1000);
        break;

        case 'e': // analog read
        pinMode(command[1],INPUT);
        Serial.print("Pin Value ="); 
        Serial.println(analogRead(command[1]));   
        delay(1000);
        break;
       
       message_pos = 0;     //Reset for the next message
      }
   }
   delay (60);
   
 } 
    



   } 
  
   delay (30);
 }
  //My Code starts Here
  //climber.move(255,255);

}
