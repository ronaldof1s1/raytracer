#ifndef CAMERA_H_
#define CAMERA_H_

#include "utility/Vector3.h"
#include "utility/Ray.h"
#include "View_Plane.h"
#include <cmath>
# define M_PI           3.14159265358979323846

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
	virtual Ray get_ray(double u, double v);

	Ray get_ray(double row, double col, int n_rows, int n_cols);


	void set_frame(Point3 look_from, Point3 look_at, Vector3 up);

};

#endif
