#include "Raytrace.h"
#include <cstdio>
#include <cmath>

	void Raytrace::render(std::ofstream &output_image, Shader *shader, int n_samples, float gamma=2.2){
			int n_cols = image.get_width();
			int n_rows = image.get_height();
			Scene scene = image.get_scene();

			//start writing image file
      output_image << "P" << image.get_type() << "\n"
                	 << n_cols << " " << n_rows << "\n"
                	 << image.get_max_color() << "\n";

      for ( int row = n_rows-1 ; row >= 0 ; --row ) // Y
      {
				// float percentage =  100.0*float(n_rows-row)/float(n_rows*n_cols) ;
				// printf("%f\r", percentage);
        for( int col = 0 ; col < n_cols ; col++ ) // X
        {
          RGB c(0);
					//getting antialiasing samples
          for(int sample = 0; sample < n_samples; sample++){
						//generate random u and v for antialiasing;
						std::knuth_b random_generator(sample);
						float u = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);
						float v = std::generate_canonical<float, std::numeric_limits<float>::digits> (random_generator);

						// generate Ray shoot from camera to point (row + u, col + v)
					  Ray r = image.get_camera().get_ray(row + u, col + v, n_rows, n_cols);

            // Determine the color of one of the rays, as it travels through the virtual space.
            c += shader->shade( r, scene );

          }
            c /= n_samples; //mean color from antialiasing
            int ir = int( 255.99f * std::pow(c[RGB::R], 1/gamma) );
            int ig = int( 255.99f * std::pow(c[RGB::G], 1/gamma) );
            int ib = int( 255.99f * std::pow(c[RGB::B], 1/gamma) );
            output_image << ir << " " << ig << " " << ib << "\n";
        }
	    }

	}
