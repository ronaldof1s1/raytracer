#include "Camera.h"

Ray Camera::get_ray(double row, double col, int n_rows, int n_cols){
  double u = double(col) / double( n_cols ); // walked u% of the horizontal dimension of the view plane.
  double v = double(row) / double( n_rows ); // walked v% of the vertical dimension of the view plane.

  return get_ray(u, v);
};

void set_frame(Point3 look_from, Point3 look_at, Vector3 up){
  // vector3 u, v, w;
  vecto3 gaze = look_from - look_at;

  Vector3 w = unit_vector(gaze);
  Vector3 u = unit_vector(cross(up, w));
  Vector3 v = unit_vector(cross(w,u));

  frame = std::make_tuple(u,v,w);

  origin = look_from;
};
