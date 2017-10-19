#ifndef LIGHT_H_
#define LIGHT_H_

#include <utility>

class Light {

  public:
    RGB intensity;

    //Constructors
    Light(){
      intensity = RGB(1.0,1.0,1.0);
    }
    Light(RGB rgb){
      intensity = rgb;
    }

    RGB get_intensity(){ return intensity; }

    virtual std::pair<Vector3, RGB> Illuminate(Point3 p) const = 0;
  };
#endif
