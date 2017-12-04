#include "Plane.h"

#include <cmath>
#include <iostream>

#define MIN 0.01

void Plane::set_transformation_matrix(Matrix t) {
	origin = t.transform_point(origin);
	normal = t.transform_vector(normal);
	normal = unit_vector(normal);
	transform = t;
}

bool Plane::hit(const Ray & r, double t_min, double t_max, hit_record & rec) {

  double denom = dot(normal, r.get_direction());
	if(denom < 0) {
		Vector3 planeOrayO = unit_vector(origin - r.get_origin());
		double t = dot(planeOrayO, normal)/denom;
		if(t >= 0) {
			if(t < t_max and t > t_min) {
				// std::cout << "rec.material " <<  rec.material->albedo << '\n';
				rec.t = t;
				rec.p = r.point_at(t);
				rec.p += normal*MIN;
				rec.normal = normal;
				rec.material = material;
				return true;
			}
		}
	}
	return false;
}
