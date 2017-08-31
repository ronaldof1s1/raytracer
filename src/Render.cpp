#include <iostream>
#include <list>
#include <fstream>
#include <cmath>
#include <limits>
#include <ctime>
#include "../libs/hitables/Sphere.h"
#include "../libs/Raytrace.h"
#include "../libs/Image.h"
#include "../libs/shaders/Normal_to_RGB.h"
#include "../libs/shaders/Depth_map.h"
//#include "../libs/shaders/Lambertian.h"
//#include "../libs/shaders/Blinn-Phong.h"

using namespace utility;

int main(int argc, char const *argv[])
{
    clock_t total_time_start = clock();
    int n_cols = 400;
    int n_rows = 200;

    int n_samples = 16;

    std::ofstream output_image(argv[1], std::ios::out);
    if (output_image.is_open()){


      //=== Defining our 'camera'
      Point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
      Vector3 vertical(0, 2, 0); // Vertical dimension of the view plane.
      Vector3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
      Point3 origin(0, 0, 0); // the camera'sbui   origin.

      Camera cam(lower_left_corner, vertical, horizontal, origin);

      //creating Scene:
      std::list< Hitable* > *objects = new std::list< Hitable* >() ;
      Scene scene(*objects);

      //filling with Spheres
      Sphere s1(Point3(0,-100.5,-3), 99.f);
      scene.add_object(&s1);
      Sphere s2(Point3(0.3, 0, -1), 0.4);
      scene.add_object(&s2);
      Sphere s3(Point3(0, 1, -2), 0.6);
      scene.add_object(&s3);
      Sphere s4(Point3(-0.4, 0, -3), 0.7);
      scene.add_object(&s4);

      Image image(3, 255, n_cols, n_rows, scene, cam);

      Raytrace my_raytrace(image);

      Shader *shader = new Depth_map();

      clock_t start = clock();

      my_raytrace.render(output_image, shader, n_samples);
      std::cout << "time to Raytrace: " << (double)(clock() - start)/CLOCKS_PER_SEC << std::endl
                << "time total: " << (double)(clock() - total_time_start)/CLOCKS_PER_SEC << std::endl;

      output_image.close();
    }
    else{
      std::cout << "could not open output image file" << std::endl;
    }
    return 0;
}
