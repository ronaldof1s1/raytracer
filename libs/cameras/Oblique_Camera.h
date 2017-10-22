#ifndef _OBLIQUE_CAMERA_H_
#define _OBLIQUE_CAMERA_H_

#include "../Camera.h"

class Oblique_Camera : public Camera{
public:
  Oblique_Camera(Point3 look_from, Point3 look_at, Point3 up, Point3 left,
                Point3 right, Point3 bottom, Point3 top, Vector3 vp_normal = Vector3(0)):Camera(look_from, look_at, up){
                Vector3 direction;
                // std::cout << "vp_normal" << vp_normal << '\n';
                if (vp_normal == Vector3(0) ){//and vp_normal.Y == 0.00 ){and vp_normal.Z == 0.00 ){
                  direction = -std::get<2>(frame);
                }
                else{
                  direction = vp_normal;
                }
                // std::cout << "direction" << direction << '\n';
                Vector3 llc = origin + left + bottom;
                Vector3 ha = origin + right - left;
                Vector3 va = origin + top - bottom;
                view_plane = View_Plane(llc, ha, va, direction);
  }

  Ray get_ray(double row, double col, int n_rows, int n_cols){
    Camera::get_ray(row, col, n_rows, n_cols);
  }
  Ray get_ray(double u, double v) const override;
};

Ray Oblique_Camera::get_ray(double u, double v) const{
  Point3 ray_origin = view_plane.lower_left_corner + u*view_plane.horizontal_axis + v*view_plane.vertical_axis;
  Vector3 ray_target = view_plane.normal;
  return Ray(ray_origin, ray_target);
}


#endif
