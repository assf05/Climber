/* h code for Climber library
v0.1.2b
by Ido Azran & Assf Saces
2022
*/
#ifndef CLIMBER_H
#define CLIMBER_H

 class Climber {
  
  private:
    //int speed = 700;
    //void movefromedge(char axis, char direction);
    
  public:
    Climber(); 
    void begin();   
    float GetYaw(); //gets gyro yaw angle 
    void GyroYawCalibration(); //Calibrats gyro for correct yaw reading
    void move(int left_speed, int right_speed); //move with right and left speed 
    void BluetoothUpdateVariables(); //function for the "Update Variables" option 
    void AutoMode(); //function for the "Auto Mode" option
    void BluetoothController(); // function for the "Manual Control" option
    char getCharBT();//return value from BTSerial
 };

#endif 
