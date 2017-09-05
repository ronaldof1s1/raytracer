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
#include "../libs/shaders/Recursive.h"
#include "../libs/materials/Lambertian.h"
#include "../libs/shaders/Blinn_Phong.h"

using namespace utility;

int main(int argc, char const *argv[])
{
    clock_t total_time_start = clock();
    int n_cols = 1200;
    int n_rows = 600;

    int n_samples = 1;

    std::ofstream output_image(argv[1], std::ios::out);
    if (output_image.is_open()){


      //=== Defining our 'camera'
      Point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
      Vector3 vertical(0, 2, 0); // Vertical dimension of the view plane.
      Vector3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
      Point3 origin(0, 0, 0); // the camera'sbui   origin.

      Camera cam(lower_left_corner, vertical, horizontal, origin);

      //creating Scene:
      std::list< Hitable* > *objects = new std::list< Hitable* >();
      Background bg;
      bg.lower_left = RGB(1.f);
      bg.upper_left = RGB(1.f);
      bg.lower_right = RGB(1.f);
      bg.upper_right = RGB(1.f);
      std::list< Light > lights;
      Light light;
      light.source = Vector3(20,10,5);
      // light.intensity = Vector3(0.5,0.5,0.5);
      light.intensity = RGB(1.f);
      lights.push_back(light);
      Scene scene(*objects, bg, lights, RGB(0.4));

      //filling with Spheres
      /*Sphere s1(Point3(0,-100.5,-30), 100.f, new Lambertian(RGB(0,1,0)));
      scene.add_object(&s1);
      Sphere s2(Point3(0.3, 0, -1), 0.4, new Lambertian(RGB(1,0,0)));
      scene.add_object(&s2);
      Sphere s3(Point3(0, 1, -2), 0.6, new Lambertian(RGB(0,0,1)));
      scene.add_object(&s3);
      Sphere s4(Point3(-0.4, 0, -3), 0.7, new Lambertian(RGB(1,1,1)));
      scene.add_object(&s4);*/

      Sphere s1(Point3(0,-100.5,-1), 100.f, new Material(RGB(0.1), RGB(0.4), RGB(1.f), 5));
      scene.add_object(&s1);
      Sphere s2(Point3(0,0,-1), 0.4, new Material(RGB(0.1), RGB(0.0,0.3,0.8), RGB(0.9), 32));
      scene.add_object(&s2);

      Image image(3, 255, n_cols, n_rows, scene, cam);

      Raytrace my_raytrace(image);

      // Shader *shader = new Depth_map();
      // Shader *shader = new Normal_to_RGB();
      Shader *shader = new Blinn_Phong(false, true, true);

      clock_t start = clock();

      my_raytrace.render(output_image, shader, n_samples, 2.f);
      std::cout << "time to Raytrace: " << (double)(clock() - start)/CLOCKS_PER_SEC << std::endl
                << "time total: " << (double)(clock() - total_time_start)/CLOCKS_PER_SEC << std::endl;

      output_image.close();
    }
    else{
      std::cout << "could not open output image file" << std::endl;
    }
    return 0;
}
