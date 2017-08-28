#include <iostream>
#include <list>
#include <fstream>
#include <cmath>
#include <limits>
#include "../utility/vector3.h"
#include "../utility/ray.h"
#include "../utility/camera.h"
#include "../utility/scene.h"
#include "../utility/hitables/sphere.h"
#include "../utility/Raytrace.h"


using namespace utility;

int main(int argc, char const *argv[])
{
    int n_cols = 1200;
    int n_rows = 600;

    int depth_map = 1;
    int rgb_normal = 0;

    int n_samples = 16;

    std::ofstream image(argv[1], std::ios::out);

    //=== Defining our 'camera'
    point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
    vector3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    vector3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
    point3 origin(0, 0, 0); // the camera's origin.

    camera cam(lower_left_corner, vertical, horizontal, origin);

    //creating scene:
    std::list< hitable* > *objects = new std::list< hitable* >() ;
    scene scene_(*objects);

    //filling with spheres
    sphere s1(point3(0,-100.5,-3), 99.f);
    scene_.add_object(&s1);
    sphere s2(point3(0.3, 0, -1), 0.4);
    scene_.add_object(&s2);
    sphere s3(point3(0, 1, -2), 0.6);
    scene_.add_object(&s3);
    sphere s4(point3(-0.4, 0, -3), 0.7);
    scene_.add_object(&s4);

    Raytrace my_raytrace(cam, scene_, n_rows, n_cols);
    my_raytrace.render(image, rgb_normal, n_samples);

    return 0;
}
