#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include <iostream>
#include <fstream>
#include <random>
#include "camera.h"
#include "Scene.h"

class Raytrace {
	camera cam;
	Scene sce;
	int n_cols;
	int n_rows;
	// //fields

	// +resource_manager

	// +background

public:
		Raytrace(camera &c, Scene &s, int rows, int cols){
			cam = c;
			sce = s;
			n_rows = rows;
			n_cols = cols;
		}

	void render(std::ofstream &image, int rgb_normal, int n_samples);

	RGB depth_map(const Ray &r, Point3 &p, float max_depth);

	RGB color( const Ray &r_, int depth_or_normal, Scene &Scene_ );
	// //methods
	// +init
	// +hit_anything
	// +render
};
#include "Raytrace.cpp"
#endif
