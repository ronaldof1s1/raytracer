#ifndef CAMERA_H_
#define CAMERA_H_

#include "vector3.h"
#include "ray.h"

class camera{
public:
	// fields
	vector3 lower_left_corner;
	vector3 vertical_axis;
	vector3 horizontal_axis;
	vector3 origin;

	// TODO: constructors & getters
	camera(){};
	camera(point3 llc, vector3 va, vector3 ha, point3 origin_){
		lower_left_corner = llc;
		vertical_axis = va;
		horizontal_axis = ha;
		origin = origin_;
	};

	vector3 get_lower_left_corner() {return lower_left_corner;};
	vector3 get_vertical_axis() {return vertical_axis;};
	vector3 get_horizontal_axis() {return horizontal_axis;};
	vector3 get_origin() {return origin;};

	Ray get_ray(float u, float v){
		// Determine the ray's direction, based on the pixel coordinate (col,row).
		// We are mapping (matching) the view plane (vp) to the image.
		// To create a ray we need: (a) an origin, and (b) an end point.
		//
		// (a) The ray's origin is the origin of the camera frame (which is the same as the world's frame).
		//
		// (b) To get the end point of ray we just have to 'walk' from the
		// vp's origin + horizontal displacement (proportional to 'col') +
		// vertical displacement (proportional to 'row').
		point3 end_point = lower_left_corner + u*horizontal_axis + v*vertical_axis;
		Ray r (origin, end_point - origin);
		return r;
	}

	Ray get_ray(float row, float col, int n_rows, int n_cols){
		float u = float(col) / float( n_cols ); // walked u% of the horizontal dimension of the view plane.
		float v = float(row) / float( n_rows ); // walked v% of the vertical dimension of the view plane.

		return get_ray(u, v);
	}

};

#endif
