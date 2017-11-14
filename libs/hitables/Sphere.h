#ifndef SPHERE_H_
#define SPHERE_H_

#include "../Hitable.h"
#include "../materials/Lambertian.h"
class Sphere : public Hitable{

  double radius;
  Point3 center;
  Matrix transform_inverse;

public:
    Sphere(){
      center = Point3(0); //create sphere on the center
      radius = 0.d; //sphere with 0 radius
    };
    Sphere(Point3 cen, double r){
      center = cen;
      radius = r;
      material = new Lambertian(); //standard material
    }
    Sphere(Point3 cen, double radius_, Material *mat_){
      center = cen;
      radius = radius_;
      material = mat_;
    }

    Point3 get_center(){return center;}
    double get_radius(){return radius;}

    virtual void set_transformation_matrix(Matrix t){
      transform = t;
      transform_inverse = inverse_matrix(t);
    }

    virtual bool hit( const Ray & r, double t_min, double t_max, hit_record & rec) override ;
};

#include "Sphere.cpp"

#endif
