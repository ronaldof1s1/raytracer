#ifndef HITABLE_H_
#define HITABLE_H_

#include "utility/Ray.h"
#include "Material.h"

struct hit_record {
	float t;
  Point3  p;
  Vector3 normal;
	Material *material;
};

class Hitable {

public:
  Point3 center;
	Material *material;

  Point3 get_center(){return center;}

  virtual bool hit(const Ray & r, float t_min, float t_max, hit_record & rec) const = 0;
};

#endif
