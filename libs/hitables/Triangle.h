#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "../Hitable.h"

class Triangle : public Hitable{
public:
  Point3 v0, v1, v2;

  Triangle(){
    v0 = v1 = v2 = Point3(0);
  }
  Triangle(Point3 v0_, Point3 v1_, Point3 v2_){
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
  }
  Triangle(Point3 v0_, Point3 v1_, Point3 v2_, Material* mat){
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
    material = mat;
  }

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) const;

};

bool Triangle::hit(const Ray & r, double t_min, double t_max, hit_record & rec) const{

}

#endif
