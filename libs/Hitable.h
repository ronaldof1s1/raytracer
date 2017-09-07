#ifndef HITABLE_H_
#define HITABLE_H_

#include "utility/Ray.h"
#include "Material.h"

//struct to the point that was hit
struct hit_record {
	double t; //the t at the point
  Point3  p; //the point that was hit
  Vector3 normal; //the normal of the point in relation to the object
	Material *material; //the material that was hit
};

class Hitable {
protected:
	  Point3 center; //all objects have a center
		Material *material; //all objects have a material

public:

  Point3 get_center(){return center;}
	Material* get_material(){return material;}

  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) const = 0;
};

#endif
