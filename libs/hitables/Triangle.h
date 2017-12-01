#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#define EPSILON 0.0001

#include "../Hitable.h"

class Triangle : public Hitable{
public:

  Point3 v0, v1, v2, origin;

  Vector3 edge_1, edge_2, normal;

  bool culling;

  Triangle(bool cull = true){
    origin = v0 = v1 = v2 = Point3(0);

    edge_1 = v1 - v0;
    edge_2 = v2 - v0;

    normal = unit_vector(cross(edge_1, edge_2));

    culling = cull;
  }
  Triangle(Point3 v0_, Point3 v1_, Point3 v2_, bool cull = true){
    origin = v0 = v0_;
    v1 = v1_;
    v2 = v2_;

    edge_1 = v1 - v0;
    edge_2 = v2 - v0;

    normal = unit_vector(cross(edge_1, edge_2));

    culling = cull;
  }
  Triangle(Point3 v0_, Point3 v1_, Point3 v2_, Material* mat, bool cull = true){
    origin = v0 = v0_;
    v1 = v1_;
    v2 = v2_;

    edge_1 = v1 - v0;
    edge_2 = v2 - v0;

    normal = unit_vector(cross(edge_1, edge_2));

    material = mat;

    culling = cull;
    // std::cout << v0 << " " << v1 << " " << v2 << '\n';
  }

  virtual void set_transformation_matrix(Matrix t) override {
    transform = t;
    v0 = transform.transform_point(v0);
    v1 = transform.transform_point(v1);
    v2 = transform.transform_point(v2);
    edge_1 = v1 - v0;
    edge_2 = v2 - v0;
    // std::cout << "v0" << v0 << '\n';
    // std::cout << "v1" << v1 << '\n';
    // std::cout << "v2" << v2 << '\n';
  }

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) override ;

};

#include "Triangle.cpp"

#endif
