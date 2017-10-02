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
      vp_normal = -std::get<2>(frame);
    }

    vp_v = cross(std::get<0>(frame), vp_normal);
    vp_u = cross(vp_normal, vp_u);

    llc = origin + dist_to_focus - half_width*vp_u - half_height*vp_v - vp_normal;
    ha = 2*half_width*vp_u;
    va = 2*half_height*vp_v;
    view_plane = View_Plane(llc,ha,va, vp_normal);
  }

  virtual Ray get_ray(double u, double v);
};

Ray Perspective_Camera::get_ray(double u, double v){
  Vector3 target = view_plane.lower_left_corner + u*view_plane.horizontal_axis + v*view_plane.vertical_axis;
  return Ray(origin, unit_vector(target));
}

#endif
