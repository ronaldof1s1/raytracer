#ifndef _PERSPECTIVE_CAMERA_H_
#define _PERSPECTIVE_CAMERA_H_

#include "../Camera.h"
#include <random>

// std::knuth_b random_generator(3);

class Perspective_Camera : public Camera{
public:
  double vertical_fov;
  double aspect_ratio;
  double focal_distance;
  double focal_opening;

  Perspective_Camera( Point3 look_from, Vector3 look_at, Vector3 up,
                      double vfov, double aspec, double dist_to_focus, double ap, Vector3 vp_normal = Vector3(0)):Camera(look_from,look_at,up){

    aspect_ratio = aspec;
    vertical_fov = vfov;
    focal_distance = dist_to_focus;
    focal_opening = ap;

    double theta = vfov * M_PI / 180;
    double half_height = std::tan(theta/2);
    double half_width = aspect_ratio * half_height;

    Vector3 direction = vp_normal;
    if (vp_normal == Vector3(0)){
      direction = -std::get<2>(frame);
    }

    Vector3 u = std::get<0>(frame);
    Vector3 v = std::get<1>(frame);

    Vector3 llc = origin + direction*focal_distance - half_width*u - half_height*v;
    Vector3 ha = 2*half_width*u;
    Vector3 va = 2*half_height*v;

    view_plane = View_Plane(llc,ha,va, direction);
  }

  Ray get_ray(double row, double col, int n_rows, int n_cols){
    Camera::get_ray(row, col, n_rows, n_cols);
  }
  Ray get_ray(double u, double v) const override;
};

Ray Perspective_Camera::get_ray(double u, double v) const {
  Vector3 target = view_plane.lower_left_corner + u*view_plane.horizontal_axis + v*view_plane.vertical_axis;
  // target = unit_vector(target);
  Ray r(origin, target);
  if(focal_opening > 0){
    double x = (std::generate_canonical<double, std::numeric_limits<double>::digits>(random_generator)-0.5) * focal_opening;
    double y = (std::generate_canonical<double, std::numeric_limits<double>::digits>(random_generator)-0.5) * focal_opening;

    double focal_target = (focal_distance + origin.Z) / target.Z;
    // std::cout << "focal_target: " << focal_target << '\n';
    Point3 focus_point = r.point_at(focal_target);
    // std::cout << "focal_point: " << focus_point << '\n';

    Point3 new_origin = origin + Vector3(x, y, 0);
    // std::cout << "new_origin" << new_origin << '\n';
    target = unit_vector(focus_point - new_origin);
    // std::cout << "new_target" << target << '\n';
    r = Ray(new_origin, target);
  }
  return r;
}

#endif
