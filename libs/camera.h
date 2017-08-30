#ifndef CAMERA_H_
#define CAMERA_H_

#include "utility\Vector3.h"
#include "utility\Ray.h"

class Camera{
public:
	// fields
	Vector3 lower_left_corner;
	Vector3 vertical_axis;
	Vector3 horizontal_axis;
	Vector3 origin;

	// TODO: constructors & getters
	Camera(){};
	Camera(Point3 llc, Vector3 va, Vector3 ha, Point3 origin_){
		lower_left_corner = llc;
		vertical_axis = va;
		horizontal_axis = ha;
		origin = origin_;
	};

	Vector3 get_lower_left_corner() {return lower_left_corner;};
	Vector3 get_vertical_axis() {return vertical_axis;};
	Vector3 get_horizontal_axis() {return horizontal_axis;};
	Vector3 get_origin() {return origin;};

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
		Point3 end_point = lower_left_corner + u*horizontal_axis + v*vertical_axis;
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
