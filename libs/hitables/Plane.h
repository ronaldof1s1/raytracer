#ifndef PLANE_H_
#define PLANE_H_

#include "../Hitable.h"

class Plane : public Hitable {
public:
	Point3 origin;
	Vector3 normal;
	Plane () {};
	Plane(Point3 o, Vector3 n, Material *mat) {
    origin = o;
    normal = n;
    material = mat;
  }

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) override ;

	virtual void set_transformation_matrix(Matrix t) override;

};

#include "Plane.cpp"

#endif
