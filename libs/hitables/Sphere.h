#ifndef SPHERE_H_
#define SPHERE_H_

#include "../Hitable.h"
#include "../materials/Lambertian.h"
class Sphere : public Hitable{


public:
    float radius;
    Sphere(){
      center = Point3(0,0,0);
      radius = 0.f;
    };
    Sphere(Point3 cen, float r){
      center = cen;
      radius = r;
      material = new Lambertian();
    }
    Sphere(Point3 cen, float radius_, Material *mat_){
      center = cen;
      radius = radius_;
      material = mat_;
    }

    float get_radius(){return radius;}

    virtual bool hit( const Ray & r, float t_min, float t_max, hit_record & rec) const;
};

#include "Sphere.cpp"

#endif
