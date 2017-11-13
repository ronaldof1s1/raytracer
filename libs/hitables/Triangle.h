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

  virtual void set_transformation_matrix(Matrix t){
    transform = t;
    v0 = transform.transform_point(v0);
    v1 = transform.transform_point(v1);
    v2 = transform.transform_point(v2);
    edge_1 = v1 - v0;
    edge_2 = v2 - v0;
    std::cout << "v0" << v0 << '\n';
    std::cout << "v1" << v1 << '\n';
    std::cout << "v2" << v2 << '\n';
  }

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) const;

};

bool Triangle::hit(const Ray & r, double t_min, double t_max, hit_record & rec) const{


  double u, v, t;

  // P = D X E_2
  Vector3 P = cross(r.get_direction(), edge_2);

  double det = dot(edge_1, P);
  double inv_det = 1/det;


  //if bacward culling is active
  if(culling){

    if(det < EPSILON){
      return false;
    }

    //T = O - v0
    Vector3 T = r.get_origin() - v0;

    u = dot(T, P);

    if(u < 0.0 or u > det){
      return false;
    }
    //Q = T x E_1
    Vector3 Q = cross(T, edge_1);

    v = dot(r.get_direction(), Q);

    if(v < 0.0 or u + v > det){
      return false;
    }

    t = dot(edge_2, Q);


    t *= inv_det;
    u *= inv_det;
    v *= inv_det;

  }
  else{
    if(det > -EPSILON and det < EPSILON){
      return false;
    }

    Vector3 T = r.get_origin() - v0;

    u = dot(T,P) * inv_det;

    if(u < 0.0 or u > 1.0){
      return false;
    }

    Vector3 Q = cross(T, edge_1);

    v = dot(r.get_direction(), Q) * inv_det;

    if(v < 0.0 or u + v > 1.0){
      return false;
    }

    t = dot(edge_2, Q) * inv_det;
  }

  if(t < t_max and t > t_min){
    rec.t = t;
    rec.p = r.point_at(t);
    rec.material = material;
    rec.normal = normal;
  }
  // std::cout << "aqui" << '\n';
  return true;
}

#endif
