#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_
#include <cmath>
#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

class Spotlight : public Light{
public:
  Point3 source;
  Vector3 direction;
  double opening_angle;
  double atenuation;

  Spotlight():Light(){source = Vector3(0); direction = Vector3(0); opening_angle = 0; atenuation = 1;}
  Spotlight(Vector3 dir, double angle = 90):Light(){source = Point3(0); direction = dir; opening_angle = angle; atenuation = 1;}
  Spotlight(Point3 src, Vector3 dir, Vector3 intensity, double angle = 90):Light(intensity){
    source = src;
    direction = dir;
    opening_angle = angle;
  }
  Spotlight(Point3 src, Vector3 dir, Vector3 intensity, double angle = 90, double att = 1):Light(intensity){
    source = src;
    direction = dir;
    opening_angle = angle;
    atenuation = att;
  }

std::pair<Vector3, RGB> Illuminate(Point3 point) const override{
  Vector3 light_ray = unit_vector(point - source);
  double cos_ray_direction = dot(light_ray, direction);
  Vector3 this_intensity = RGB(0);
  if(cos_ray_direction > std::cos(opening_angle) ){
    this_intensity = intensity * cos_ray_direction * atenuation;
  }
  return std::make_pair(-light_ray, this_intensity);
}

};

#endif
