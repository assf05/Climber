#ifndef CLIMBER_H
#define CLIMBER_H

 class Climber {
  
  private:
    //int speed = 700;
    //void movefromedge(char axis, char direction);
    
  public:
    Climber(); 
    void begin();   
    void move(int left_speed, int right_speed); //move with right and left speed 
 };

#endif 