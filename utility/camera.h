#ifndef CAMERA_H_
#define CAMERA_H_

#include "vector3.h"

class camera{
public:
	// fields
	vector3 lower_left_corner;
	vector3 vertical_axis;
	vector3 horizontal_axis;
	vector3 origin;

	// TODO: constructors & getters
};

#endif