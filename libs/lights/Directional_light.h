#ifndef DIRECTIONAL_LIGHT_H_
#define DIRECTIONAL_LIGHT_H_

#include "../Light.h"

class Directional_light : public Light {

  public:
    Vector3 direction;

    //Constructors
    Directional_light():Light(){ direction = Vector3(0.0,0.0,0.0); }
    Directional_light(RGB intensity):Light(intensity){ direction = Point3(0.0,0.0,0.0); }
    Directional_light(Point3 dir, RGB intensity):Light(intensity){ direction = dir; }

    std::pair<Vector3, RGB> Illuminate(Point3 point) const override{
        return std::make_pair(direction, intensity);
    }
  };

#endif
