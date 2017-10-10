#ifndef DIRECTIONAL_H_
#define DIRECTIONAL_H_

#include "../Light.h"

class Directional : Light {

  public:
    Vector3 direction;
    
    //Constructors
    Directional():Light(){ direction = Vector3(0.0,0.0,0.0); }
    Directional(RGB intensity):Light(intensity){ direction = Point3(0.0,0.0,0.0); }
    Directional(Point3 _direction, RGB intensity):Light(intensity){ direction = _direcetion; }
    
    virtual Vector3 get_direction(Point3 point){
        return direction;
    }
  };
  
#endif
