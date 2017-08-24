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

		void render(std::ofstream &image, int rgb_normal){
			if (image.is_open()) {

		      image << "P3\n"
		                << n_cols << " " << n_rows << "\n"
		                << "255\n";

		      for ( auto row = n_rows-1 ; row >= 0 ; --row ) // Y
		      {
		          for( auto col = 0 ; col < n_cols ; col++ ) // X
		          {
		              Ray r = cam.get_ray(row, col, n_rows, n_cols);

		              // Determine the color of the ray, as it travels through the virtual space.
		              auto c = color( r, rgb_normal, sce );
		              int ir = int( 255.99f * c[rgb::R] );
		              int ig = int( 255.99f * c[rgb::G] );
		              int ib = int( 255.99f * c[rgb::B] );
		              image << ir << " " << ig << " " << ib << "\n";
		          }
		      }
		      image.close();
	    	}
		}

	rgb depth_map(const Ray &r, point3 &p, float max_depth){
		
	  rgb background_color(1,1,1);
	  rgb foreground_color(0,0,0);

	  float depth = (p - r.get_origin()).length();
	  depth /= max_depth;

	  // evading color overflow
	  if(depth > 1){
	    depth = 1.0;
	  }

	  rgb depth_color = (1.0 - depth) * (foreground_color) + depth * background_color;

	  return depth_color;
	}

	rgb color( const Ray &r_, int depth_or_normal, scene &scene_ )
	{

	    float max_t = std::numeric_limits<float>::max();
	    float min_t = 0.0;

	    vector3 rgb_to_paint;
	    hit_record rec;

	    if(scene_.hit_anything(r_, min_t, max_t, rec)){

	      if(depth_or_normal == 1) {
	          float max_depth = 4.0;
	          rgb_to_paint = depth_map(r_, rec.p, max_depth);
	      }
	      else {
	          rgb_to_paint = 0.5 * (rec.normal + vector3(1,1,1));
	      }

	      return rgb_to_paint;
	    }


	    if(depth_or_normal == 1){
	      //white background
	      rgb bg(1,1,1);
	      return bg;
	    }

	    rgb bottom (0.5, 0.7, 1.0 );
	    rgb top(1,1,1);

	    rgb unit_direction = unit_vector(r_.get_direction());
	    float i = 0.5*(unit_direction.y() + 1);
	    rgb_to_paint = (1-i) * top + i * bottom;

	    return rgb_to_paint; // Stub, replace it accordingly
	}
	// //methods
	// +init
	// +hit_anything
	// +render
};

#endif
