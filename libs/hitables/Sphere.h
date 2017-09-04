#ifndef SPHERE_H_
#define SPHERE_H_

#include "../Hitable.h"
#include "../materials/Matte.h"
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
      mat = new Matte();
    }
    Sphere(Point3 cen, float radius_, Material *mat_){
      center = cen;
      radius = radius_;
      mat = mat_;
    }

    float get_radius(){return radius;}

    virtual bool hit( const Ray & r, float t_min, float t_max, hit_record & rec) const;
};

#include "Sphere.cpp"

#endif