#include "Plane.h"

#include <cmath>
#include <iostream>

#define MIN 0.00001

void Plane::set_transformation_matrix(Matrix t) {
	origin = t.transform_point(origin);
	normal = t.transform_vector(normal);
	normal = unit_vector(normal);
}

bool Plane::hit(const Ray & r, double t_min, double t_max, hit_record & rec) {

  double denom = dot(normal, ray.get_direction());
	if(denom < 0) {
		Vector3 planeOrayO = unit_vector(origin - ray.get_origin());
		double t = dot(planeOrayO, normal)/denom;
		if(t >= 0) {
			if(t < t_max and t < t_min) {
				rec.t = t;
				rec.p = ray.at(t);
				rec.p += normal*MIN;
				rec.normal = normal;
				rec.material = mat;
				return true;
			}
		}
	}
	return false;
}
