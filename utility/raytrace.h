#ifndef RAYTRACE_H_
#define RAYTRACE_H_

#include "camera.h"
#include "scene.h"

class raytrace {
	camera cam;
	scene sce;
	int n_cols;
	int n_rows;
	// //fields
	
	// +resource_manager
	
	// +background
	raytrace(camera c, scene s, int rows, int cols){
		cam = c;
		sce = s;
		n_rows = rows;
		n_cols = cols;
	}
	// //methods
	// +init
	// +hit_anything
	// +render
}

#endif
