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
	Camera(Point3 look_from, Point3 look_at, Vector3 up){
		Vector3 gaze = look_from - look_at;
		Vector3 u,v,w;

	  w = unit_vector(gaze);
	  u = unit_vector(cross(up, w));
	  v = unit_vector(cross(w,u));
		frame = std::make_tuple(u,v,w);
	  origin = look_from;
	};


	//Getters
	Vector3 get_lower_left_corner() {return view_plane.lower_left_corner;};
	Vector3 get_vertical_axis() {return view_plane.vertical_axis;};
	Vector3 get_horizontal_axis() {return view_plane.horizontal_axis;};
	Vector3 get_origin() {return origin;};

	//Getting ray shoot from the camera
	// virtual Ray get_ray(double u, double v); 		TEMPORARY

	Ray get_ray(double row, double col, int n_rows, int n_cols);

	virtual Ray get_ray(double u, double v) const = 0;

};

Ray Camera::get_ray(double row, double col, int n_rows, int n_cols){
  double u = double(col) / double( n_cols ); // walked u% of the horizontal dimension of the view plane.
  double v = double(row) / double( n_rows ); // walked v% of the vertical dimension of the view plane.

  return get_ray(u, v);
}



#endif
