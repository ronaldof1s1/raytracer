#include "Plane.h"


#define MIN 0.01

void Plane::set_transformation_matrix(Matrix t) {
	t1->set_transformation_matrix(t);
	t2->set_transformation_matrix(t);
}

bool Plane::hit(const Ray & r, double t_min, double t_max, hit_record & rec) {

	if(t1->hit(r, t_min, t_max, rec)){
		// std::cout << "hit t1" << '\n';
		return true;
	}
	else if(t2->hit(r, t_min, t_max, rec)){
		// std::cout << "hit t2" << '\n';
		return true;
	}
	else{
		return false;
	}

}
