#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#define EPSILON 0.000001

#include "../Hitable.h"

class Triangle : public Hitable{
public:
  Point3 v0, v1, v2;
  bool culling;
  Triangle(bool cull = true){
    v0 = v1 = v2 = Point3(0);
    culling = cull;
  }
  Triangle(Point3 v0_, Point3 v1_, Point3 v2_, bool cull = true){
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
    culling = cull;
  }
  Triangle(Point3 v0_, Point3 v1_, Point3 v2_, Material* mat, bool cull = true){
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
    material = mat;
    culling = cull;
    // std::cout << v0 << " " << v1 << " " << v2 << '\n';
  }

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) const;

};

bool Triangle::hit(const Ray & r, double t_min, double t_max, hit_record & rec) const{
  Vector3 origin = r.get_origin();
  Vector3 direction = r.get_direction();
  Vector3 edge_1, edge_2;
  edge_1 = v1 - v0;
  edge_2 = v2 - v0;

  double u, v, t;

  // P = D X E_2
  Vector3 P = cross(direction, edge_2);

  double det = dot(edge_1, P);
  double inv_det = 1/det;


  //if bacward culling is active
  if(culling){

    if(det < EPSILON){
      return false;
    }

    //T = O - v0
    Vector3 T = origin - v0;

    u = dot(T, P);

    if(u < 0.0 or u > det){
      return false;
    }
    //Q = T x E_1
    Vector3 Q = cross(T, edge_1);

    v = dot(direction, Q);

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

    Vector3 T = origin - v0;

    u = dot(T,P) * inv_det;

    if(u < 0.0 or u > 1.0){
      return false;
    }

    Vector3 Q = cross(T, edge_1);

    v = dot(direction, Q) * inv_det;

    if(v < 0.0 or u + v > 1.0){
      return false;
    }

    t = dot(edge_2, Q) * inv_det;

    if (t< EPSILON){
      return false;
    }
    
  }

  if(t < t_max and t > t_min){
    rec.t = t;
    rec.p = r.point_at(t);
    rec.material = material;
    Vector3 normal = cross(edge_1, edge_2);
    rec.normal = unit_vector(normal);
  }
  return true;
}

#endif
