#ifndef HITABLE_H_
#define HITABLE_H_

#include "ray.h"

struct hit_record {
	float t;
  vector3  p;
  vector3 normal;
};

class hitable {
public:
  virtual bool hit(const ray & r, float t_min, float t_max, hit_record & rec) const = 0;
};

#endif