#ifndef _OBLIQUE_CAMERA_H_
#define _OBLIQUE_CAMERA_H_

#include "../Camera.h"

class Oblique_Camera : public Camera{
public:
  Oblique_Camera(Point3 left, Point3 right, Point3 bottom, Point3 top, Vector3 vp_normal = Vector3(0)):Camera(){

    if (vp_normal.X() == 0 && vp_normal.Y() == 0 && vp_normal.Z() == 0){
      vp_normal = -std::get<2>(frame);
    }

    direction = unit_vector(vp_normal);
    Vector3 llc = left + bottom;
    Vector3 ha = right - left;
    Vector3 va = top - bottom;
    view_plane = View_Plane(llc, ha, va, vp_normal);
  }

  Oblique_Camera(Point3 left, Point3 bottom, Vector3 vp_normal = Vector3(0)):Camera(){
    Oblique_Camera(left, -left, bottom, -bottom, vp_normal);
  }

  virtual Ray get_ray(double u, double v);
};

Ray Oblique_Camera::get_ray(double u, double v){
  Point3 ray_origin = view_plane.lower_left_corner + u*view_plane.horizontal_axis + v*view_plane.vertical_axis;
  Vector3 ray_target = view_plane.normal;
  return Ray(ray_origin, ray_target);
}


#endif
