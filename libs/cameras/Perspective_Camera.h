#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include "../Camera.h"

class Perspective_Camera : public Camera{
public:
  double vertical_fov;
  double aspect_ratio;
  double focal_distance;

  Perspective_Camera( double vfov, double aspec, double dist_to_focus, Vector3 vp_normal = Vector3(0)):Camera(){
    double theta = vfov * M_PI / 180;
    double half_height = tan(theta/2);
    double half_width = aspect * half_height;

    if (vp_normal.X() == 0 && vp_normal.Y() == 0 && vp_normal.Z() == 0){
      vp_normal = std::get<2>(frame);
    }

  }

  virtual Ray get_ray(double u, double v);
};

Ray Perspective_Camera::get_ray(double u, double v){
  return Ray(Point3(0), Vector3(0));
}

#endif
