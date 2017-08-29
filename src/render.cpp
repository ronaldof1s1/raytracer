#include <iostream>
#include <list>
#include <fstream>
#include <cmath>
#include <limits>
#include "../libs/utility/Vector3.h"
#include "../libs/utility/Ray.h"
#include "../libs/Camera.h"
#include "../libs/Scene.h"
#include "../libs/hitables/Sphere.h"
#include "../libs/Raytrace.h"


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
    Point3 lower_left_corner( -2, -1, -1 ); // lower left corner of the view plane.
    Vector3 vertical(0, 2, 0); // Vertical dimension of the view plane.
    Vector3 horizontal( 4, 0, 0 ); // Horizontal dimension of the view plane.
    Point3 origin(0, 0, 0); // the camera's origin.

    camera cam(lower_left_corner, vertical, horizontal, origin);

    //creating Scene:
    std::list< Hitable* > *objects = new std::list< Hitable* >() ;
    Scene Scene_(*objects);

    //filling with Spheres
    Sphere s1(Point3(0,-100.5,-3), 99.f);
    Scene_.add_object(&s1);
    Sphere s2(Point3(0.3, 0, -1), 0.4);
    Scene_.add_object(&s2);
    Sphere s3(Point3(0, 1, -2), 0.6);
    Scene_.add_object(&s3);
    Sphere s4(Point3(-0.4, 0, -3), 0.7);
    Scene_.add_object(&s4);

    Raytrace my_raytrace(cam, Scene_, n_rows, n_cols);
    my_raytrace.render(image, rgb_normal, n_samples);

    return 0;
}
