#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include <iostream>
#include <fstream>
#include "camera.h"
#include "scene.h"

class Raytrace {
	camera cam;
	scene sce;
	int n_cols;
	int n_rows;
	// //fields

	// +resource_manager

	// +background

public:
		Raytrace(camera &c, scene &s, int rows, int cols){
			cam = c;
			sce = s;
			n_rows = rows;
			n_cols = cols;
		}

	void render(std::ofstream &image, int rgb_normal);

	rgb depth_map(const Ray &r, point3 &p, float max_depth);

	rgb color( const Ray &r_, int depth_or_normal, scene &scene_ );
	// //methods
	// +init
	// +hit_anything
	// +render
};
#include "Raytrace.cpp"
#endif
