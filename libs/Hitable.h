#ifndef HITABLE_H_
#define HITABLE_H_

#include "utility/Ray.h"
#include "utility/Matrix.h"
#include "Material.h"

class Hitable {
protected:
	  Material *material; //all objects have a material
		Matrix transform;
public:

	Matrix get_transformation_matrix(){return transform;}
	Material* get_material(){return material;}

	virtual void set_transformation_matrix(Matrix t){}
  virtual bool hit(const Ray & r, double t_min, double t_max, hit_record & rec) const = 0;
};

#endif
