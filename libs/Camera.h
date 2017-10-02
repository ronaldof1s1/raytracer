#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "View_Plane.h"
#include <cmath>
#define M_PI           3.14159265358979323846

class Camera{
public:
	// fields
	Point3 origin;
	View_Plane view_plane;
	std::tuple<Vector3, Vector3, Vector3> frame; //x,y,z ortogonal

	// Constructors & getters
	Camera(){

	};

	//Getters
	Vector3 get_lower_left_corner() {return view_plane.lower_left_corner;};
	Vector3 get_vertical_axis() {return view_plane.vertical_axis;};
	Vector3 get_horizontal_axis() {return view_plane.horizontal_axis;};
	Vector3 get_origin() {return origin;};
	std::tuple<Vector3, Vector3, Vector3> get_frame() {return frame;};

	//Getting ray shoot from the camera
	// virtual Ray get_ray(double u, double v); 		TEMPORARY
	inline Ray get_ray(double u, double v);

	inline Ray get_ray(double row, double col, int n_rows, int n_cols);


	inline void set_frame(Point3 look_from, Point3 look_at, Vector3 up);

};

inline Ray Camera::get_ray(double row, double col, int n_rows, int n_cols){
  double u = double(col) / double( n_cols ); // walked u% of the horizontal dimension of the view plane.
  double v = double(row) / double( n_rows ); // walked v% of the vertical dimension of the view plane.

  return get_ray(u, v);
}

inline void Camera::set_frame(Point3 look_from, Point3 look_at, Vector3 up){
  // vector3 u, v, w;
  Vector3 gaze = look_from - look_at;

  w = unit_vector(gaze);
  u = unit_vector(cross(up, w));
  v = unit_vector(cross(w,u));

  origin = look_from;
}

inline Ray Camera::get_ray(double u, double v){
  Vector3 target = view_plane.lower_left_corner + u* view_plane.horizontal_axis + v*view_plane.vertical_axis;
  return Ray(origin, target);
}


#endif
