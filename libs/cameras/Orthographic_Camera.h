#ifndef _ORTHOGRAPHIC_CAMERA_H_
#define _ORTHOGRAPHIC_CAMERA_H_

#include "../Camera.h"

class Orthographic_Camera : public Camera{
public:

  // Orthographic_Camera(double left, double right, double bottom, double top, Vector3 vp_normal = Vector3(0)):Camera(){
  //
  // }

  virtual Ray get_ray(double u, double v);
};

Ray Orthographic_Camera::get_ray(double u, double v){
  Point3 ray_origin = origin + u*std::get<0>(frame) + v*std::get<1>(frame);
  Vector3 ray_target = unit_vector(-std::get<2>);
  return Ray(ray_origin, ray_target);
}


#endif
