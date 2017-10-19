#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include "../Light.h"

class Pointlight : public Light {

  public:
    Point3 source;
    // double attenuation;
    // double light_radius;
    //Constructors
    Pointlight():Light(){ source = Point3(0.0,0.0,0.0); }
    Pointlight(RGB intensity):Light(intensity){ source = Point3(0.0,0.0,0.0); }
    Pointlight(Point3 src, RGB intensity):Light(intensity){ source = src; }

    Point3 get_source(){ return source; }

    std::pair<Vector3, RGB> Illuminate(Point3 point) const override {
        Vector3 light_direction = unit_vector(source - point);
        return std::make_pair(light_direction, intensity);
    }
  };

#endif
