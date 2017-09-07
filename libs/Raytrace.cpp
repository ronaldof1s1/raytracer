#include "Raytrace.h"
#include <cstdio>
#include <cmath>

	void gamma_correction(RGB &rgb, double gamma = 2.2f){
		double r = std::pow(rgb[RGB::R], 1.d/gamma);
		double g = std::pow(rgb[RGB::G], 1.d/gamma);
		double b = std::pow(rgb[RGB::B], 1.d/gamma);
		rgb = RGB(r,g,b);
	}

	void Raytrace::render(std::ofstream &output_image, Shader *shader, int n_samples){
			int n_cols = image.get_width();
			int n_rows = image.get_height();
			Scene scene = image.get_scene();

			//start writing image file
      output_image << "P" << image.get_type() << "\n"
                	 << n_cols << " " << n_rows << "\n"
                	 << image.get_max_color() << "\n";

      for ( int row = n_rows-1 ; row >= 0 ; --row ) // Y
      {
				int percentage =  int(100.0*double(n_rows-row)/double(n_rows)) ;
				std::cout << "\r" << percentage << "%" << std::flush;
        for( int col = 0 ; col < n_cols ; col++ ) // X
        {
          RGB color(0);
					//getting antialiasing samples
          for(int sample = 0; sample < n_samples; sample++){
						//generate random u and v for antialiasing;
						std::knuth_b random_generator(sample);
						double u = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);
						double v = std::generate_canonical<double, std::numeric_limits<double>::digits> (random_generator);

						// generate Ray shoot from camera to point (row + u, col + v)
					  Ray r = image.get_camera().get_ray(row + u, col + v, n_rows, n_cols);

            // Determine the color of one of the rays, as it travels through the virtual space.
            color += shader->shade( r, scene );

          }
            color /= n_samples; //mean color from antialiasing

						gamma_correction(color);

            int ir = int( 255.99f * color[RGB::R] );
            int ig = int( 255.99f * color[RGB::G] );
            int ib = int( 255.99f * color[RGB::B] );
            output_image << ir << " " << ig << " " << ib << "\n";
        }
	    }
			std::cout << std::endl;

	}
