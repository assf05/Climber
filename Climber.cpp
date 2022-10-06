#include "HardwareSerial.h"
/* cpp code for Climber library
v0.0.2
using Default I2C pins : SCL = A5, SDA = A4 
by Ido Azran & Assf Saces
2022
*/
 #include "Arduino.h"
 #include "Climber.h"
 #include <Wire.h>
 #include <GY521.h> 
 #include <SoftwareSerial.h>
 

static const int en1 = 1; 
static const int en2 = 2; 
static const int enA = 5; // connected to l298n, left motor

static const int en3 = 3; 
static const int en4 = 4; 
static const int enB = 6; // connected to l298n, right motor

GY521 sensor(0x69); // connected to gyro, I2C Address 0x69
float yaw;

SoftwareSerial MyBlue(2, 3); // RX | TX 


Climber::Climber() {
  //this->speed = speed; //assign motors speed or - delay
}

void Climber::begin() {
  Serial.begin(115200);
  MyBlue.begin(115200);
  Wire.begin();
  delay(100);

  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521");
    delay(1000);
  }  

  Serial.println("Climber Initiated");
  pinMode(enA,OUTPUT); 
  pinMode(enB,OUTPUT); 
 
 Serial.println("cli works only with bluetooth terminal");
 MyBlue.println("cli works only with bluetooth terminal");
}


void Climber::move(int left_speed, int right_speed) { //moves both motors with speed(pwm)
  Serial.println("move activated");
  Serial.print("Right Speed =");
  Serial.print(right_speed);
  Serial.print("  |  Left Speed =");
  Serial.println(left_speed); 
  analogWrite(enA, left_speed); //moves left moter with left_speed(pwm)
  analogWrite(enB, right_speed);//moves left moter with right_speed(pwm)
 }

 float Climber::GetYaw() {
  sensor.read();
  yaw = sensor.getYaw();
  Serial.println("Yaw Angle =  " + yaw);
  return yaw;
}

void Climber::GyroYawCalibration() {
  Serial.println("Starting Calibration");
  sensor.setAccelSensitivity(2);  // 8g
  sensor.setGyroSensitivity(1);   // 500 degrees/s
  sensor.aye = -0.002;
  sensor.gye = -6.436;
}
 
void Climber::cli() { 
 while (MyBlue.available() > 0) { 
   char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;
   char inByte = MyBlue.read();   //Read the next available byte in the serial receive buffer
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
     {
     message[message_pos] = inByte;  //Add the incoming byte to our message
     message_pos++;
     }
     //Full message received...
     else
     {
      message[message_pos] = '\0';     //Add null character to string
      MyBlue.println(message);     //echo the message to terminal
        
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
        MyBlue.println("Pin SET");   
        delay(1000);
        break;
       case 'l': // Set port to LOW
        pinMode(command[1],OUTPUT);
        digitalWrite(command[1],LOW);
        MyBlue.println("Pin RESET");   
        delay(1000);
        break;
       
       case 'a': // analog Write to pwm ports
        pinMode(command[1],OUTPUT);
        analogWrite(command[1],command[2]);
        MyBlue.println("writing analog value");   
        delay(1000);
        break;

       case 'r': // digital read
        pinMode(command[1],INPUT);
        MyBlue.print("Pin Value ="); 
        MyBlue.println(digitalRead(command[1]));   
        delay(1000);
        break;

        case 'e': // analog read
        pinMode(command[1],INPUT);
        MyBlue.print("Pin Value ="); 
        MyBlue.println(analogRead(command[1]));   
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
}
