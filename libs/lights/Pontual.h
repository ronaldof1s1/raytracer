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

    virtual std::pair<Vector3, RGB> get_direction(Point3 point) const {
        Vector3 light_direction = unit_vector(source - point);
        return std::make_pair(light_direction, intensity);
    }
  };

#endif
