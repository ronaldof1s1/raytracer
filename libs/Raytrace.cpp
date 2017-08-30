#include "Raytrace.h"

	void Raytrace::render(std::ofstream &output_image, int rgb_normal, int n_samples){
		if (output_image.is_open()) {
			int n_cols = image.get_width();
			int n_rows = image.get_height();
			Scene scene = image.get_scene();
      output_image << "P" << image.get_type() << "\n"
                << n_cols << " " << n_rows << "\n"
                << image.get_max_color() << "\n";

      for ( int row = n_rows-1 ; row >= 0 ; --row ) // Y
      {
          for( int col = 0 ; col < n_cols ; col++ ) // X
          {
            RGB c(0,0,0);
						//getting antialiasing samples
            for(int sample = 0; sample < n_samples; sample++){
							//generate random u and v for antialiasing;
							std::mt19937 random_generator(time(0));
							float u = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
							float v = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);

							// generate Ray shoot from camera to point (row + u, col + v)
						  Ray r = image.get_camera().get_ray(row + u, col + v, n_rows, n_cols);

              // Determine the color of one of the rays, as it travels through the virtual space.
              c += color( r, rgb_normal, scene );

            }
              c /= n_samples; //mean color from antialiasing
              int ir = int( 255.99f * c[RGB::R] );
              int ig = int( 255.99f * c[RGB::G] );
              int ib = int( 255.99f * c[RGB::B] );
              output_image << ir << " " << ig << " " << ib << "\n";
          }
	      }
	      output_image.close();
    	}
	}

	RGB Raytrace::depth_map(const Ray &r, Point3 &p, float max_depth){

	  RGB background_color(1,1,1);
	  RGB foreground_color(0,0,0);

	  float depth = (p - r.get_origin()).length();
	  depth /= max_depth;

	  // evading color overflow
	  if(depth > 1){
	    depth = 1.0;
	  }

	  RGB depth_color = (1.0 - depth) * (foreground_color) + depth * background_color;

	  return depth_color;
	}

	RGB Raytrace::color( const Ray &r_, int depth_or_normal, Scene &Scene_ )
	{

	    float max_t = std::numeric_limits<float>::max();
	    float min_t = 0.0;

	    Vector3 rgb_to_paint;
	    hit_record rec;

	    if(Scene_.hit_anything(r_, min_t, max_t, rec)){

	      if(depth_or_normal == 1) {
	          float max_depth = 4.0;
	          rgb_to_paint = depth_map(r_, rec.p, max_depth);
	      }
	      else {
	          rgb_to_paint = 0.5 * (rec.normal + Vector3(1,1,1));
	      }

	      return rgb_to_paint;
	    }


	    if(depth_or_normal == 1){
	      //white background
	      RGB bg(1,1,1);
	      return bg;
	    }

	    RGB bottom (0.5, 0.7, 1.0 );
	    RGB top(1,1,1);

	    RGB unit_direction = unit_vector(r_.get_direction());
	    float i = 0.5*(unit_direction.y() + 1);
	    rgb_to_paint = (1-i) * top + i * bottom;

	    return rgb_to_paint; // Stub, replace it accordingly
	}
