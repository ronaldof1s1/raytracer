#ifndef HITABLE_H_
#define HITABLE_H_

#include "utility\ray.h"

struct hit_record {
	float t;
  point3  p;
  vector3 normal;
};

class hitable {

public:
  point3 center;
  point3 get_center(){return center;}

  virtual bool hit(const Ray & r, float t_min, float t_max, hit_record & rec) const = 0;
};

#endif
