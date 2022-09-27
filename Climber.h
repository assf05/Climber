/* h code for Climber library
v0.0.1
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
    void GetYaw(); //gets gyro yaw angle 
    void GyroYawCalibration(); //Calibrats gyro for correct yaw reading
    void move(int left_speed, int right_speed); //move with right and left speed


 };

#endif 
