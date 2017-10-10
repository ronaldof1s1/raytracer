#ifndef PONTUAL_H_
#define PONTUAL_H_

#include "../Light.h"

class Pontual : Light {

  public:
    Point3 source;
    
    //Constructors
    Pontual():Light(){ source = Point3(0.0,0.0,0.0); }
    Pontual(RGB intensity):Light(intensity){ source = Point3(0.0,0.0,0.0); }
    Pontual(Point3 _source, RGB intensity):Light(intensity){ source = _source; }
    
    Point3 get_source(){ return source; }
    
    virtual Vector3 get_direction(Point3 point){
        Vector3 light_direction = unit_vector(source - point);
        return light_direction;
    }
  };
  
#endif
