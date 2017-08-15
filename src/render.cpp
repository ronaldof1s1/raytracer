#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include "../utility/vector3.h"
#include "../utility/ray.h"
#include "../utility/camera.h"

using namespace utility;
/*
 *  In the near future we'll want to refactor our project to become
 *  something like the code below.
 */
#ifdef TRADITIONAL_RT
Image Raytrace (Camera cam, Scene scene, int width, int height)
{
    Image image = new Image (width, height) ;
    for (int i = 0 ; i < height ; i++)
        for (int j = 0 ; j < width ; j++) {
            Ray ray = RayThruPixel (cam, i, j) ;
            Intersection hit = Intersect (ray, scene) ;
            image[i][j] = FindColor (hit) ;
            }
    return image ;
}
#endif

float hit_sphere(const Ray & r, const point3 & center, const float radius) {
    auto oc = r.get_origin() - center;
    float a = dot(r.get_direction(), r.get_direction());
    float b = 2 * dot(oc, r.get_direction());
    float c = dot(oc,oc) - radius*radius;

    float delta = b*b - 4*a*c;


    if(delta < 0){
        return -1.0;
    }
    else{
        auto f1 = (-b + sqrt(delta))/(2.0*a);
        auto f2 = (-b - sqrt(delta))/(2.0*a);

        // returns the minimum positive root
        // or any negative root (if the two are negatives)
        if(f1 >= 0){
          if(f1 < f2 || f2 < 0){
            return f1;
          }
        }
        return f2;
    }
}
vector3 normal_calculation(const Ray & r, const point3 & center, const float t) {
  vector3 normal;
  vector3 unit(1,1,1);
  normal = unit_vector(r.point_at(t) - center);
  normal += unit;
  normal *= 0.5;
  return normal;
}

rgb depth_map(const Ray & r, float t, float max_depth){
  rgb background_color(1,1,1);
  rgb foreground_color(0,0,0);

  float depth = (r.point_at(t) - r.get_origin()).length();
  depth /= max_depth;

  // evading color overflow
    if(depth > 1){
      depth = 1.0;
    }

  rgb depth_color = (1.0 - depth) * (foreground_color) + depth * background_color;
  return depth_color;
}

rgb color( const Ray & r_, int depth_or_normal )
{
    // spheres
    int max_spheres = 4;
    point3 centers[max_spheres];
    float radius[max_spheres];
    centers[0] = point3(0,-100.5,-3);  radius[0] = 99.f;
    centers[1] = point3(0.3, 0, -1);    radius[1] = 0.4;
    centers[2] = point3(0, 1, -2);      radius [2] = 0.6;
    centers[3] = point3(-0.4, 0, -3);   radius [3] = 0.7;

    float min_t = std::numeric_limits<float>::max();

    vector3 rgb_to_paint;
    bool hit_any_sphere = false;

    for (int i = 0; i < max_spheres; i++) {
      float t = hit_sphere(r_, centers[i], radius[i]);

      if(t > 0 && t < min_t){
        hit_any_sphere = true;
        min_t = t;

        if(depth_or_normal == 1) {
          float max_depth = 4.0;
          rgb_to_paint = depth_map(r_, t, max_depth);
        }
        else {
          rgb_to_paint = normal_calculation(r_, centers[i], t);
        }
      }
    }
    if(hit_any_sphere){
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
    unit_direction = (1-i)*top + i* bottom;

    return unit_direction; // Stub, replace it accordingly
}

int main(int argc, char const *argv[])
{
    int n_cols{ 1200 };
    int n_rows{ 600 };

    std::ofstream image(argv[1], std::ios::out);
    if (image.is_open()) {
      image << "P3\n"
                << n_cols << " " << n_rows << "\n"
                << "255\n";


      //=== Defining our 'camera'
      point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
      vector3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
      vector3 vertical(0, 2, 0); // Vertical dimension of the view plane.
      point3 origin(0, 0, 0); // the camera's origin.

      camera cam (lower_left_corner, horizontal, vertical, origin);
       // NOTICE: We loop rows from bottom to top.
      for ( auto row = n_rows-1 ; row >= 0 ; --row ) // Y
      {
          for( auto col = 0 ; col < n_cols ; col++ ) // X
          {
              Ray r = cam.get_ray(row, col, n_rows, n_cols);

              // Determine the color of the ray, as it travels through the virtual space.
              auto c = color( r, 1 );
              int ir = int( 255.99f * c[rgb::R] );
              int ig = int( 255.99f * c[rgb::G] );
              int ib = int( 255.99f * c[rgb::B] );
              image << ir << " " << ig << " " << ib << "\n";
          }
      }
      image.close();
    }

    return 0;
}
