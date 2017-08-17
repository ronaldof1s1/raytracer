#include <iostream>
#include <cmath>
#include "../utility/vector3.h"
#include "../utility/ray.h"
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

        if(f1 >= 0){
          if(f1 < f2 || f2 < 0){
            return f1;
          }
        }
        return f2;
    }
}


rgb color( const Ray & r_ )
{
    // sphere 1
    point3 center(0,0,-1);
    float radius = 0.5;
    // esferas: TODO
    // {point3(0,-100.5,-30), 100.f},
    // {point3(0.3, 0, -1), 0.4},
    // {point3(0, 1, -2), 0.6},
    // {point3(-0.4, 0, -3), 0.7}


    auto t = hit_sphere(r_, center, radius);
    //t = -1;
    if(t > 0){
      vector3 unit(1,1,1);
      auto normal = unit_vector(r_.point_at(t) - center);
      normal += unit;
      normal *= 0.5;
      return normal;
    }

    rgb bottom (0.5, 0.7, 1.0 );
    rgb top(1,1,1);

    rgb unit_direction = unit_vector(r_.get_direction());
    float i = 0.5*(unit_direction.y() + 1);
    unit_direction = (1-i)*top + i* bottom;

    return unit_direction; // Stub, replace it accordingly
}
int main( void )
{
    int n_cols{ 200 };
    int n_rows{ 100 };

    std::cout << "P3\n"
              << n_cols << " " << n_rows << "\n"
              << "255\n";


    //=== Defining our 'camera'
    point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
    vector3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
    vector3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    point3 origin(0, 0, 0); // the camera's origin.

     // NOTICE: We loop rows from bottom to top.
    for ( auto row = n_rows-1 ; row >= 0 ; --row ) // Y
    {
        for( auto col = 0 ; col < n_cols ; col++ ) // X
        {
            // Determine how much we have 'walked' on the image: in [0,1]
            auto u = float(col) / float( n_cols ); // walked u% of the horizontal dimension of the view plane.
            auto v = float(row) / float( n_rows ); // walked v% of the vertical dimension of the view plane.

            // Determine the ray's direction, based on the pixel coordinate (col,row).
            // We are mapping (matching) the view plane (vp) to the image.
            // To create a ray we need: (a) an origin, and (b) an end point.
            //
            // (a) The ray's origin is the origin of the camera frame (which is the same as the world's frame).
            //
            // (b) To get the end point of ray we just have to 'walk' from the
            // vp's origin + horizontal displacement (proportional to 'col') +
            // vertical displacement (proportional to 'row').
            point3 end_point = lower_left_corner + u*horizontal + v*vertical ;

            // The ray:
            Ray r( origin, end_point - origin );

            // Determine the color of the ray, as it travels through the virtual space.
            auto c = color( r );
            int ir = int( 255.99f * c[rgb::R] );
            int ig = int( 255.99f * c[rgb::G] );
            int ib = int( 255.99f * c[rgb::B] );
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    return 0;
}
