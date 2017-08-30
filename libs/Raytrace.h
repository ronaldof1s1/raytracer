#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include <iostream>
#include <fstream>
#include <random>
#include "Image.h"
class Raytrace {
	Image image;
	// +resource_manager

	// +background

public:
	Raytrace(Image img){image = img;}

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
