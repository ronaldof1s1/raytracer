#ifndef _ORTOGONAL_CAMERA_H_
#define _ORTOGONAL_CAMERA_H_

#include "../Camera.h"

class Ortogonal_Camera : public Camera{
public:

  Ortogonal_Camera(double left, double right, double bottom, double top, Vector3 vp_normal = Vector3(0)):Camera(){

  }

  virtual Ray get_ray(double u, double v);
};

Ray Perspective_Camera::get_ray(double u, double v){
  return Ray(Point3(0), Vector3(0));
}


#endif
