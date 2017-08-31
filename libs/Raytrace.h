#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include <iostream>
#include <fstream>
#include <random>
#include "Image.h"
#include "Shader.h"
class Raytrace {
	Image image;
	// +resource_manager

	// +background

public:
	Raytrace(Image img){image = img;}

	void render(std::ofstream &image, Shader *shader, int n_samples);

	// //methods
	// +init
	// +hit_anything
};
#include "Raytrace.cpp"
#endif
